
#include <linux/semaphore.h>/*For sema_init(),down(),up()*/
#include <linux/jiffies.h>/*For jiffies  HZ = 100 */
#include <linux/miscdevice.h>/*For struct miscdevice ...*/
#include <linux/module.h>/*For module specific items*/
#include <linux/types.h>/*for standard types (like size_t) */
#include <linux/kernel.h>/*For printk/panic/...*/
#include <linux/device.h>/*For struct class*/
#include <linux/string.h>/*For strlen...*/
#include <linux/errno.h> /*For the -ENODEV/...value*/
#include <linux/init.h>/*For  __init/__exit/....*/
#include <linux/fs.h>/*For struct file_operations*/
#include <linux/cdev.h>/*For struct cdev/cdev_init/...*/
#include <asm/uaccess.h>/*For copy_to_user/ ...*/
#include <linux/errno.h>/*For error symbol*/
#include <linux/slab.h>  /*for kmalloc()*/
#include <linux/sched.h>  
#include <linux/delay.h>
#include <linux/spinlock_types.h>
#include <linux/spinlock.h>
#include <linux/poll.h>

#include <asm/irq.h>
#include <asm/io.h>
#include <asm/arch/regs-gpio.h>
#include <asm/hardware.h>

volatile unsigned long *gpfcon;
volatile unsigned long *gpfdat;

volatile unsigned long *gpgcon;
volatile unsigned long *gpgdat;


void my_tasklet_func(unsigned long); //定义一个处理函数:
DECLARE_TASKLET(my_tasklet,my_tasklet_func,data); // 定 义 一 个 tasklet 结 构my_tasklet,与 my_tasklet_func(data)函数相关联


#define DEV_SIZE 100
#define  MISC_NAME "chardrv_test"

/*
*declare the struct my_data, contains private data
* kbuf :the data kernel keeps.
*cur_size: the current size of the kbuf:
*sem:	the semaphore of contrl concurrency 
*/
struct my_data{
		
	char kbuf[DEV_SIZE];
	unsigned int cur_size;
	int val;
	struct semaphore sem; 
	static wait_queue_head_t my_queue;
	static int read_flag;
	static struct fasync_struct *my_async_queue;
};


struct pin_desc{
	unsigned int key_val;
	unsigned int pin;
	
};

struct my_data *devp ;//decalre a structure pointer, then use kmalloc() to allocate space for it 

int misc_open(struct inode *node,struct file *filp)
{


	filp->private_data = devp; // give the structure pointer to filp->private_data
	printk("This is misc_open\n");
	return 0;
}
	



/*****************************************************************************************
***	Description:		
***			read data from kernel	
***
***	Return Value:
***			If read sucessfully, return the bytes that have readed.
*******************************************************************************************/

static ssize_t misc_read(struct file *filp, char __user *buf, size_t count, loff_t *offset)
{
	int ret;
	struct my_data *dev = filp->private_data;


	if(wait_event_interruptible(dev->my_queue,dev->read_flag!=0))
	{
		return -EBUSY;
	}
	
	if(down_interruptible(&dev->sem))
	{
		return -EBUSY;
	}
	
	dev->read_flag = 0;
	
	
		
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
	
	
	up(&dev->sem);	

	return ret;
}


/*****************************************************************************************
***	Description:		
***			write data to kernel	
***
***	Return Value:
***			If write sucessfully, return the bytes that have written.
*******************************************************************************************/
static ssize_t misc_write(struct file *filp, const char __user *buf, size_t count, loff_t *offset)
{
	int ret;
	

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
	
	kill_fasync(&dev->my_async_queue, SIGIO, POLL_IN);
	
	wake_up_interruptible(&dev->my_queue);

	printk("sleepping is over, you can write \n");	
	return ret;
}


static unsigned int misc_poll(struct file *filp, struct poll_table_struct *wait)
{
/*
	void poll_wait(struct file *filp, wait_queue_heat_t *queue, poll_table * wait);
*/
	unsigned int mask = 0;
	
	struct my_data *dev = filp->private_data;
	poll_wait(filp,&my_queue,wait);
	
	if(read_flag)
	{
		mask |= POLLIN | POLLRDNORM;
	}
	
	return mask;
	
}

 static int misc_fasync(int fd, struct file *filp, int on)
 {
	struct my_data *dev = filp->private_data;
	return fasync_helper(fd, filp, on, &dev->my_async_queue);
 }


int misc_close(struct inode *node,struct file *filp)
{
	printk("This is misc_close\n");
	misc_fasync(-1,filp,0);
	return 0;
}
/*
*The struct file_operations
*/
struct file_operations misc_fops={
	.open	= misc_open,
	.release = misc_close,
	.read	= misc_read,
	.write	= misc_write,
	.poll	= misc_poll,
	.fasync = misc_fasync,
};

/*
*fill the content of struct miscdevice
*/
static struct miscdevice misc_dev=
{
	.minor = MISC_DYNAMIC_MINOR,//Dynamically allocate minor device
	.name = MISC_NAME,
	.fops = &misc_fops,
};

/*
*Loading function
*/
static int __init misc_init(void)
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

	/*
	*initialize the semaphore
	*
	*note:
	*	after kernel 2.6.25, init_NUTEX() is abandoned. Now we use sema_init() instead.
	*/
	sema_init(&devp->sem,1);
	printk("Hello kernel!\n");
	return 0;
}


/*
*Unistall function
*/
static void __exit misc_exit(void)
{
    printk("Goodbye kernel!\n");

	if(devp != NULL)	
	{
		kfree(devp);//delete structure pointer
		devp = NULL;
	}
	misc_deregister(&misc_dev);	
}

module_init(misc_init);
module_exit(misc_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Albert");
MODULE_VERSION("1.1");
MODULE_DESCRIPTION("A simple driver about get current time and count the cost time");












