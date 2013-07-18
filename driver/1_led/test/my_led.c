#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#include <asm/irq.h>
#include <asm/io.h>
#include <asm/arch/regs-gpio.h>
#include <asm/hardware.h>
#include <linux/proc_fs.h>

#include <linux/module.h>
#include <linux/poll.h>
#include <linux/proc_fs.h>
#include <linux/pci.h>
#include <linux/smp_lock.h>


volatile unsigned long *gpfcon = NULL;
volatile unsigned long *gpfdat = NULL;
struct proc_dir_entry *proc_parent = NULL; 


extern struct proc_dir_entry *proc_mkdir(const char *,struct proc_dir_entry *);
	
static inline struct proc_dir_entry *proc_create(const char *name, mode_t mode,
	struct proc_dir_entry *parent, const struct file_operations *proc_fops)
{
	return proc_create_data(name, mode, parent, proc_fops, NULL);
}
	

static int first_drv_open(struct inode *inode, struct file *file)
{
	//printk("first_drv_open\n");
	/* 配置GPF4,5,6为输出 */
	*gpfcon &= ~((0x3<<(4*2)) | (0x3<<(5*2)) | (0x3<<(6*2)));
	*gpfcon |= ((0x1<<(4*2)) | (0x1<<(5*2)) | (0x1<<(6*2)));
	return 0;
}

static ssize_t first_drv_write(struct file *file, const char __user *buf, size_t count, loff_t * ppos)
{
	int val;

	//printk("first_drv_write\n");

	copy_from_user(&val, buf, count); //	copy_to_user();

	if (val == 1)
	{
		// 点灯
		*gpfdat &= ~((1<<4) | (1<<5) | (1<<6));
	}
	else
	{
		// 灭灯
		*gpfdat |= (1<<4) | (1<<5) | (1<<6);
	}
	
	return 0;
}

static const struct file_operations first_drv_fops = {
    .owner  =   THIS_MODULE,    /* 这是一个宏，推向编译模块时自动创建的__this_module变量 */
    .open   =   first_drv_open,     
	.write	=	first_drv_write,	   
};


static int  create_proc(void)
{

     proc_parent= proc_mkdir("albert",NULL);//create albert diretory under /proc 
 
     if (proc_parent) {
         proc_create("led", S_IRUGO, proc_parent, &first_drv_fops);//create device node under /proc/albert
        //proc_create("my_proc", S_IRUGO, proc_parent,&proc_fops);//create device node under /proc/albert
 				//proc_create("dma", 0, NULL, &proc_dma_operations);
         
     }
     return (0);
 }
 

static void remove_proc(void)
{
	remove_proc_entry("led", NULL);
	remove_proc_entry("albert", NULL);
}
static int first_drv_init(void)
{
	if(!create_proc())
	{
		printk("Create proc device failed!!!\n");
	}
	else
	{
		printk("Create proc device successfully!\n");
	}
	gpfcon = (volatile unsigned long *)ioremap(0x56000050, 16);
	gpfdat = gpfcon + 1;

	return 0;
}

static void first_drv_exit(void)
{
	remove_proc();
	if(proc_parent != NULL)	
	{
		kfree(proc_parent);//delete structure pointer
		proc_parent = NULL;
	}
	iounmap(gpfcon);
}

module_init(first_drv_init);
module_exit(first_drv_exit);

EXPORT_SYMBOL(proc_create);
//EXPORT_SYMBOL(proc_create_data);
//EXPORT_SYMBOL(create_proc);
MODULE_LICENSE("GPL/GPI");

