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
#include <linux/workqueue.h> //for irq_bh work queue 

#define DEV_SIZE 100
#define  MISC_NAME "chardrv_test"

struct my_data{
		
	char kbuf[DEV_SIZE];
	unsigned int cur_size;
	int val;
	struct semaphore sem; 
	wait_queue_head_t my_queue;
	int read_flag;
	
	struct workqueue_struct *albert_wq; //1.定义工作队列
	struct work_struct albert_work; //2定义work结构体
};

struct my_data *devp;



static irqreturn_t my_irq(int irq, void* dev_id)
{
	printk("This is my_irq = %d\n", irq);
	queue_work(devp->albert_wq ,&devp->albert_work); //3调度任务
	return IRQ_HANDLED;
}

 void albert_bh_irq_func(unsigned long data)
 {
 	printk("hello albert, you are in bh_irq!, data[%d]\n", (int)data);
 }



static int misc_open(struct inode *node,struct file *filp)
{
	int ret1 = 0, ret2 = 0, ret3 = 0, ret4 = 0;
	filp->private_data = devp; // give the structure pointer to filp->private_data
	
		//IRQF_TRIGGER_FALLING: 下降沿触发中断
	ret1 = request_irq(IRQ_EINT0,my_irq,IRQF_TRIGGER_FALLING,"S2",NULL);
	ret2 = request_irq(IRQ_EINT2,my_irq,IRQF_TRIGGER_FALLING,"S3",NULL);
	ret3 = request_irq(IRQ_EINT11,my_irq,IRQF_TRIGGER_FALLING,"S4",NULL);
	ret4 = request_irq(IRQ_EINT19,my_irq,IRQF_TRIGGER_FALLING,"S5",NULL);

	if(ret1 || ret2 || ret3 || ret4 )
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

static struct miscdevice misc_dev=
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
	
	devp = kmalloc(sizeof(struct my_data),GFP_KERNEL);//allocate space for devp
	if(!devp)
	{
		printk("kmalloc failed!\n");
		return -ENOMEM;
	}

	memset(devp,0,sizeof(struct my_data));

	init_waitqueue_head(&devp->my_queue);

	/*
	*register the miscdevice
	*/
	ret = misc_register(&misc_dev);
	if(ret)
	{
		printk("misc_register error\n");
		return ret;
	
	}
	
	devp->albert_wq = create_workqueue("albert"); //1初始化工作对列
	INIT_WORK(&devp->albert_work, albert_bh_irq_func); //2初始化work结构体
	

	sema_init(&devp->sem,1);
	
	return ret;
	

}

static void __exit test_exit(void)
{
	free_irq(IRQ_EINT0,NULL);
	free_irq(IRQ_EINT2,NULL);
	free_irq(IRQ_EINT11,NULL);
	free_irq(IRQ_EINT19,NULL);
	flush_workqueue(devp->albert_wq); //4刷新工作队列
	destroy_workqueue(devp->albert_wq); //4注销工作队列
	kfree(devp);
	printk("goodbye kernel\n");
}

module_init(test_init);
module_exit(test_exit);
MODULE_LICENSE("GPL");
