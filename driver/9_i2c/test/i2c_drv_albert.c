#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/jiffies.h>
#include <linux/i2c.h>
#include <linux/mutex.h>





static int test_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	return 0;
}

static int test_detect(struct i2c_client *client, struct i2c_board_info *info)
{
	printk("detect i2c_driver");
	return 0;
}





static const unsigned short normal_i2c[] = { 0x50, 0x51, 0x52, 0x53, 0x54,
					0x55, 0x56, 0x57, I2C_CLIENT_END };

static unsigned short ignore = I2C_CLIENT_END;

/*
static struct i2c_client_address_data addr_data = {
	.normal_i2c	= normal_i2c,
	.probe		= &ignore,
	.ignore		= &ignore,
};
*/
static int test_remove(struct i2c_client *client)
{
/*	sysfs_remove_bin_file(&client->dev.kobj, &eeprom_attr);
	kfree(i2c_get_clientdata(client));
*/
	printk("remove i2c_driver");
	return 0;
}


static const struct i2c_device_id eeprom_id[] = {
	{ "eeprom", 0 },
	{ }
};


static struct i2c_driver i2c_test_driver = {
	.driver = {
		.name	= "albert_i2c_driver",
	},
	.probe		= test_probe,
	.remove		= test_remove,
	.id_table	= eeprom_id,

	.class		= I2C_CLASS_DDC | I2C_CLASS_SPD,
	.detect		= test_detect,
	.address_list	= normal_i2c,
};

static int __init test_init(void)
{
/*
	if (driver->attach_adapter || driver->detach_adapter
			|| driver->detach_client) {
		printk(KERN_WARNING
				"i2c-core: driver [%s] is confused\n",
				driver->driver.name);
		return -EINVAL;
	}
	*/
	int ret;

	ret = i2c_add_driver(&i2c_test_driver);
	if(ret){
		printk("i2c_add_driver Failed\n");
		return ret;
	}else 
		printk("i2c_add_driver successfully\n");

	return 0;
}

static void __exit test_exit(void)
{
	i2c_del_driver(&i2c_test_driver);
}




module_init(test_init);
module_exit(test_exit);
MODULE_AUTHOR("Albert");
MODULE_DESCRIPTION("I2C test driver");
MODULE_LICENSE("GPL");


