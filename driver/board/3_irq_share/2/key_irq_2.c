#include <linux/module.h>
#include <linux/wait.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <asm-arm/semaphore.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <asm/irq.h>
#include <asm/arch/regs-gpio.h>
#include <linux/irq.h>
#include <asm/hardware.h>
#include <linux/poll.h>
#include <linux/fs.h>/*For struct file_operations*/
#include <linux/miscdevice.h>/*For struct miscdevice ...*/
#include <linux/types.h>/*for standard types (like size_t) */
#include <linux/kernel.h>/*For printk/panic/...*/


#define DEV_SIZE 100
#define  MISC_NAME "chardrv_test2"

struct my_data{
		
	char kbuf[DEV_SIZE];
	unsigned int cur_size;
	int val;
	int dev_id;
	struct semaphore sem; 
	wait_queue_head_t my_queue;
	int read_flag;
};

struct my_data *devp1;



static irqreturn_t my_irq(int irq, void* dev_id)
{
	printk("This is my_irq = %d, *dev_id = %d\n", irq,devp1->dev_id);
	return IRQ_HANDLED;
}



static int misc_open(struct inode *node,struct file *filp)
{
	int ret1 = 0;
	filp->private_data = devp1; // give the structure pointer to filp->private_data
	
		//IRQF_TRIGGER_FALLING: 下降沿触发中断
	ret1 = request_irq(IRQ_EINT0,my_irq,IRQF_TRIGGER_FALLING | IRQF_SHARED,"anotherS2",&devp1->dev_id);

	if(ret1)
	{
		printk("request_irq error\n");
		return -1;
	}
	
	printk("This is misc_open\n");
	return ret1;
}


static int misc_close(struct inode *node,struct file *filp)
{
	printk("This is misc_close\n");

	return 0;
}


static ssize_t misc_read(struct file *filp, char __user *buf, size_t count, loff_t *offset)
{
	int ret = 0;
	struct my_data *dev = filp->private_data;


	if(wait_event_interruptible(dev->my_queue,dev->read_flag!=0))
	{
		return -EBUSY;
	}
	
	if(down_interruptible(&dev->sem))
	{
		return -EBUSY;
	}
	
	/*
	*Check read successfully or not
	*/
	if(!copy_to_user(buf,(void *)(&dev->val),count))
	{

		printk("<Read form kernel> buf is :%d\n",dev->val);
	}
	else
	 {
		ret = -EFAULT;
		up(&dev->sem);
		printk("Kernel test_read failed\n");
	}
	
	dev->read_flag = 0;
	up(&dev->sem);	

	return ret;
}

static ssize_t misc_write(struct file *filp, const char __user *buf, size_t count, loff_t *offset)
{
	int ret = 0;
	

	struct my_data *dev = filp->private_data;


	if(down_interruptible(&dev->sem))
	{
		return -EBUSY;
	}
	//return -ERESTARTSYS;
	if(!copy_from_user(&dev->val,(void *)buf,count))
	{

		printk("<write to kernel> buf is :%d\n",dev->val);
	}
	else 
	{
		ret = -EFAULT;
		up(&dev->sem);
	}
	
	
	up(&dev->sem);

	dev->read_flag = 1;

	wake_up_interruptible(&dev->my_queue);

	printk("sleepping is over, you can write \n");	
	return ret;
}

unsigned int misc_poll(struct file *filp, struct poll_table_struct *table)
{
	struct my_data *dev = filp->private_data;
	unsigned int mask = 0;

	poll_wait(filp, &dev->my_queue, table);


	if(dev->read_flag != 0)	//设备可读
		mask |= POLLIN;	

	return mask;
}


/*
*The struct file_operations
*/
struct file_operations misc_fops={
	.open = misc_open,
	.release = misc_close,
	.read = misc_read,
	.write = misc_write,
	.poll = misc_poll,
};

static struct miscdevice misc_dev1=
{
	.minor = MISC_DYNAMIC_MINOR,//Dynamically allocate minor device
	.name = MISC_NAME,
	.fops = &misc_fops,
};


/*
*EINT0
*EINT2
*EINT11
*EINT19
*/
static int __init test_init(void)
{
	int ret;
	
	devp1 = kmalloc(sizeof(struct my_data),GFP_KERNEL);//allocate space for devp
	if(!devp1)
	{
		printk("kmalloc failed!\n");
		return -ENOMEM;
	}

	memset(devp1,0,sizeof(struct my_data));

	init_waitqueue_head(&devp1->my_queue);

	devp1->dev_id = 200;
	/*
	*register the miscdevice
	*/
	ret = misc_register(&misc_dev1);
	if(ret)
	{
		printk("misc_register error\n");
		return ret;
	
	}
	

	sema_init(&devp1->sem,1);
	
	return ret;
	

}

static void __exit test_exit(void)
{
	free_irq(IRQ_EINT0,&devp1->dev_id);
	kfree(devp1);

	printk("goodbye kernel\n");
}

module_init(test_init);
module_exit(test_exit);
MODULE_LICENSE("GPL");
