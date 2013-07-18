#include <linux/proc_fs.h>
#include <asm/uaccess.h>
#include <linux/delay.h>
#include "mach/wistron_bsp_interface.h"
#include <mach/mt_gpio.h>
#include <cust_gpio_usage.h>
#include <linux/delay.h>

static char nvs_buffer[NVS_SIZE];
static struct WISTRON_NVS *nvs = (struct WISTRON_NVS *)nvs_buffer;
 
static int create_proc_dir(char *dir)
{
	struct proc_dir_entry *proc_dir;
	static int created = 0;
	
	if(created)
		goto end;

	if (!(proc_dir = proc_mkdir(dir, NULL))) {
		printk(KERN_ERR "--> %d %s %s\n", __LINE__, __func__, __FILE__);
        	return -1;
    	}
	else
		created = 1;
end:
	return 1;
}

static char ver_buf[UBOOT_VER_LEN + 1];	/* 1 byte for %NUL-terminated */
static int uboot_ver_setup(char *str)
{
	strncpy(ver_buf, str, sizeof(ver_buf) - 1);
	ver_buf[sizeof(ver_buf) - 1] = 0;

	return 1;
}
/* uboot version setup */
__setup("androidboot.bootloader=", uboot_ver_setup);

static ssize_t ubootversion_read_proc(char *page, char **start, off_t off,
		int count, int *eof, void *data)
{
	if(off > 0){
		*eof = 1;
		return 0;
	}

	return sprintf(page, "[B]%s\n", ver_buf) + 1;
}

static void create_ubootversion_proc_file(void)
{
	struct proc_dir_entry *proc_file =
		create_proc_entry(PROJ_PROC_BOOTLOADER_VER, 0444, NULL);

	if (proc_file)
		proc_file->read_proc = ubootversion_read_proc;
	else
		printk(KERN_INFO "proc file create failed!\n");
}

static ssize_t osversion_read_proc(char *page, char **start, off_t off,
		int count, int *eof, void *data)
{
	if(off > 0){
		*eof = 1;
		return 0;
	}

	return sprintf(page, "[K]%d\n", WISTRON_VERSION_STRING) + 1;
}

static void create_osversion_proc_file(void)
{
	struct proc_dir_entry *proc_file =
		create_proc_entry(PROJ_PROC_OS_VER, 0444, NULL);

	if (proc_file)
		proc_file->read_proc = osversion_read_proc;
	else
		printk(KERN_INFO "proc file create failed!\n");
}

static ssize_t manufacturer_read_proc(char *page, char **start, off_t off,
		int count, int *eof, void *data)
{
	if(off > 0){
		*eof = 1;
		return 0;
	}

	return sprintf(page, "%s\n", MANUFACTURER) + 1;
}

static void create_manufacturer_proc_file(void)
{
	struct proc_dir_entry *proc_file =
		create_proc_entry(PROJ_PROC_MANUFACTURER, 0444, NULL);

	if (proc_file)
		proc_file->read_proc = manufacturer_read_proc;
	else
		printk(KERN_INFO "proc file create failed!\n");
}

static int nvs_read(void){

	struct file *fp;
	loff_t f_ops;
	mm_segment_t old_fs;
	ssize_t result;

	fp = filp_open(NVS_DEVICE, O_RDONLY, 0); 
	if(IS_ERR(fp)){
		fp = filp_open(NVS_DEVICE_ANDROID, O_RDONLY, 0); 
	}
	if(IS_ERR(fp))
		goto fail;	

	if(!fp->f_op->read)
		goto fail_close;
	if(!fp->f_op->llseek) 
		goto fail_close;

	old_fs = get_fs();
	set_fs(get_ds());

	f_ops = fp->f_op->llseek(fp, NVS_OFFSET, 0);
	result = fp->f_op->read(fp, nvs_buffer, NVS_SIZE, &fp->f_pos);
	if(result <0)
		goto fail_close2;

	set_fs(old_fs);
	filp_close(fp, NULL);

	return 0;

fail_close2:
	set_fs(old_fs);
fail_close:
	filp_close(fp, NULL);
fail:
	return -1;
}

static int nvs_write(void){
	struct file *fp;
	loff_t f_ops;
	mm_segment_t old_fs;
	ssize_t result;

	fp = filp_open(NVS_DEVICE, O_RDWR | O_SYNC, 0); 
	if(IS_ERR(fp)){
		fp = filp_open(NVS_DEVICE_ANDROID, O_RDWR | O_SYNC, 0); 
	}
	if(IS_ERR(fp)){
		goto fail;
	}	

	if(!fp->f_op->read){
		goto fail_close;
	}
	if(!fp->f_op->llseek){ 
		goto fail_close;
	}

	old_fs = get_fs();
	set_fs(get_ds());

	f_ops = fp->f_op->llseek(fp, NVS_OFFSET, 0);
	result = fp->f_op->write(fp, nvs_buffer, NVS_SIZE, &fp->f_pos);
	if(result <0){
		goto fail_close2;
	}

	set_fs(old_fs);
	filp_close(fp, NULL);

	return 0;

fail_close2:
	set_fs(old_fs);
fail_close:
	filp_close(fp, NULL);
fail:
	return -1;
}

static ssize_t serial_mb_read_proc(char *page, char **start, off_t off,
		int count, int *eof, void *data){

	if(off > 0){
		*eof = 1;
		return 0;
	}

	nvs_read();
	return sprintf(page, "%s\n", nvs->sn_mb) + 1;
}

static ssize_t serial_mb_write_proc(struct file *filp,
		const char *buff, size_t len, loff_t *off)
{
	char messages[SN_MB_SIZE] = {0};
	
	if(len >= (SN_MB_SIZE - 1))
		len = SN_MB_SIZE -1;
	else
		len -=1;		//ignore "\n"

	if (copy_from_user(messages, buff, len))
		return -EFAULT;
	
	messages[SN_MB_SIZE-1] = 0x0;
	sprintf(nvs->sn_mb, "%s", messages);
	nvs_write();
	nvs_read();

	return strlen(buff);
}

static void create_serial_mb_proc_file(void)
{
	struct proc_dir_entry *proc_file_serial_mb =
		create_proc_entry(PROJ_PROC_SN_MB, 0666, NULL);

	if (proc_file_serial_mb){
		proc_file_serial_mb->read_proc = serial_mb_read_proc;
		proc_file_serial_mb->write_proc = (write_proc_t *)serial_mb_write_proc;
	}
	else
		printk(KERN_INFO "proc file create failed!\n");
}

static ssize_t serial_sys_read_proc(char *page, char **start, off_t off,
		int count, int *eof, void *data){

	if(off > 0){
		*eof = 1;
		return 0;
	}

	nvs_read();
	return sprintf(page, "%s\n", nvs->sn_sys) + 1;
}

static ssize_t serial_sys_write_proc(struct file *filp,
		const char *buff, size_t len, loff_t *off)
{
	char messages[SN_SYS_SIZE] = {0};
	
	if(len >= (SN_SYS_SIZE - 1))
		len = SN_SYS_SIZE -1;
	else
		len -=1;		//ignore "\n"

	if (copy_from_user(messages, buff, len))
		return -EFAULT;
	
	messages[SN_SYS_SIZE-1] = 0x0;
	sprintf(nvs->sn_sys, "%s", messages);
	nvs_write();
	nvs_read();

	return strlen(buff);
}

static void create_serial_sys_proc_file(void)
{
	struct proc_dir_entry *proc_file_serial_sys =
		create_proc_entry(PROJ_PROC_SN_SYS, 0666, NULL);

	if (proc_file_serial_sys){
		proc_file_serial_sys->read_proc = serial_sys_read_proc;
		proc_file_serial_sys->write_proc = (write_proc_t *)serial_sys_write_proc;
	}
	else
		printk(KERN_INFO "proc file create failed!\n");
}

static ssize_t imei_read_proc(char *page, char **start, off_t off,
		int count, int *eof, void *data){

	if(off > 0){
		*eof = 1;
		return 0;
	}

	nvs_read();
	return sprintf(page, "%s\n", nvs->imei) + 1;
}

static ssize_t imei_write_proc(struct file *filp,
		const char *buff, size_t len, loff_t *off)
{
	char messages[IMEI_SIZE] = {0};
	
	if(len >= (IMEI_SIZE - 1))
		len = IMEI_SIZE -1;
	else
		len -=1;		//ignore "\n"

	if (copy_from_user(messages, buff, len))
		return -EFAULT;
	
	messages[IMEI_SIZE-1] = 0x0;
	sprintf(nvs->imei, "%s", messages);
	nvs_write();
	nvs_read();

	return strlen(buff);
}

static void create_imei_proc_file(void)
{
	struct proc_dir_entry *proc_file_imei =
		create_proc_entry(PROJ_PROC_IMEI, 0666, NULL);

	if (proc_file_imei){
		proc_file_imei->read_proc = imei_read_proc;
		proc_file_imei->write_proc = (write_proc_t *)imei_write_proc;
	}
	else
		printk(KERN_INFO "proc file create failed!\n");
}

static ssize_t pcb_version_read_proc(char *page, char **start, off_t off,
		int count, int *eof, void *data){

	char messages[PCB_VER_SIZE] = {0};
	int pcb_ver0 = 1;	//gpioExt29	// SB/SC
	int pcb_ver1 = 1;	//gpioExt30	// SB/SC
	int pcb_ver2 = 0;	//gpioExt40	// SC only

	static int init = 0;
	if(!init){
		mt_set_gpio_mode(GPIOEXT29, GPIO_MODE_00);
		mt_set_gpio_dir(GPIOEXT29, GPIO_DIR_IN);
		mt_set_gpio_pull_enable(GPIOEXT29, GPIO_PULL_DISABLE);
		//mt_set_gpio_pull_select(GPIOEXT29, GPIO_PULL_UP);
	
		mt_set_gpio_mode(GPIOEXT30, GPIO_MODE_00);
		mt_set_gpio_dir(GPIOEXT30, GPIO_DIR_IN);
		mt_set_gpio_pull_enable(GPIOEXT30, GPIO_PULL_DISABLE);
		//mt_set_gpio_pull_select(GPIOEXT30, GPIO_PULL_UP);
	
		mt_set_gpio_mode(GPIOEXT40, GPIO_MODE_00);
		mt_set_gpio_dir(GPIOEXT40, GPIO_DIR_IN);
		mt_set_gpio_pull_enable(GPIOEXT40, GPIO_PULL_DISABLE);
		//mt_set_gpio_pull_select(GPIOEXT40, GPIO_PULL_UP);

		msleep(100);

		init = 1;
	}

	pcb_ver0 = mt_get_gpio_in(GPIOEXT29);
	pcb_ver1 = mt_get_gpio_in(GPIOEXT30);
	pcb_ver2 = mt_get_gpio_in(GPIOEXT40);

	if(pcb_ver0 == 0 && pcb_ver1 == 0 && pcb_ver2 == 0){
		sprintf(messages, "%s", "SA");
	}
	else if(pcb_ver0 == 1 && pcb_ver1 == 0 && pcb_ver2 == 0){
		sprintf(messages, "%s", "-2");
	}
	else if(pcb_ver0 == 0 && pcb_ver1 == 1 && pcb_ver2 == 0){
		sprintf(messages, "%s", "-1M");
	}
	else if(pcb_ver0 == 1 && pcb_ver1 == 1 && pcb_ver2 == 0){
		sprintf(messages, "%s", "SD");
	}
	else if(pcb_ver0 == 0 && pcb_ver1 == 0 && pcb_ver2 == 1){
		sprintf(messages, "%s", "SC");
	}
	else if(pcb_ver0 == 1 && pcb_ver1 == 0 && pcb_ver2 == 1){
		sprintf(messages, "%s", "-3");
	}
	else if(pcb_ver0 == 0 && pcb_ver1 == 1 && pcb_ver2 == 1){
		sprintf(messages, "%s", "-4");
	}
	else if(pcb_ver0 == 1 && pcb_ver1 == 1 && pcb_ver2 == 1){
		sprintf(messages, "%s", "-5");
	}
	else
		sprintf(messages, "%s", "N/A");

	messages[PCB_VER_SIZE-1] = 0x0;
	nvs_read();
	sprintf(nvs->pcb_version, "%s", messages);
	nvs_write();

	if(off > 0){
		*eof = 1;
		return 0;
	}

	return sprintf(page, "%s\n", messages) + 1;
}

static void create_pcb_version_proc_file(void)
{
	struct proc_dir_entry *proc_file_pcb_version =
		create_proc_entry(PROJ_PROC_PCB_VER, 0666, NULL);

	if (proc_file_pcb_version)
		proc_file_pcb_version->read_proc = pcb_version_read_proc;
	else
		printk(KERN_INFO "proc file create failed!\n");
}

static ssize_t rf_version_read_proc(char *page, char **start, off_t off,
		int count, int *eof, void *data){

	char messages[RF_VER_SIZE] = {0};
	int rf_ver0 = 1;	//gpioExt27
	int rf_ver1 = 1;	//gpioExt28

	static int init = 0;
	if(!init){
		mt_set_gpio_mode(GPIOEXT27, GPIO_MODE_00);
		mt_set_gpio_dir(GPIOEXT27, GPIO_DIR_IN);
		mt_set_gpio_pull_enable(GPIOEXT27, GPIO_PULL_DISABLE);
		//mt_set_gpio_pull_select(GPIOEXT27, GPIO_PULL_UP);
	
		mt_set_gpio_mode(GPIOEXT28, GPIO_MODE_00);
		mt_set_gpio_dir(GPIOEXT28, GPIO_DIR_IN);
		mt_set_gpio_pull_enable(GPIOEXT28, GPIO_PULL_DISABLE);
		//mt_set_gpio_pull_select(GPIOEXT28, GPIO_PULL_UP);
	

		msleep(100);
		init = 1;
	}

	rf_ver0 = mt_get_gpio_in(GPIOEXT27);
	rf_ver1 = mt_get_gpio_in(GPIOEXT28);

	if(rf_ver0 == 0 && rf_ver1 == 0){
		sprintf(messages, "%s", "3G");
	}
	else if(rf_ver0 == 1 && rf_ver1 == 0){
		sprintf(messages, "%s", "LTE");
	}
	else if(rf_ver0 == 0 && rf_ver1 == 1){
		sprintf(messages, "%s", "WIFI");
	}
	else if(rf_ver0 == 1 && rf_ver1 == 1){
		sprintf(messages, "%s", "MV");
	}
	else
		sprintf(messages, "%s", "N/A");

	messages[RF_VER_SIZE-1] = 0x0;
	nvs_read();
	sprintf(nvs->rf_version, "%s", messages);
	nvs_write();

	if(off > 0){
		*eof = 1;
		return 0;
	}

	return sprintf(page, "%s\n", messages) + 1;
}

static void create_rf_version_proc_file(void)
{
	struct proc_dir_entry *proc_file_rf_version =
		create_proc_entry(PROJ_PROC_RF_VER, 0666, NULL);

	if (proc_file_rf_version)
		proc_file_rf_version->read_proc = rf_version_read_proc;
	else
		printk(KERN_INFO "proc file create failed!\n");
}

static ssize_t wifi_country_code_read_proc(char *page, char **start, off_t off,
		int count, int *eof, void *data){

	if(off > 0){
		*eof = 1;
		return 0;
	}

	nvs_read();
	return sprintf(page, "0x%x%x\n", nvs->wifi_country_code[1], nvs->wifi_country_code[0]) + 1;
}

static ssize_t wifi_country_code_write_proc(struct file *filp,
		const char *buff, size_t len, loff_t *off)
{
	if(len < sizeof("5545"))
		return -EFAULT;
	else if(len < sizeof("0x5545"))
		goto fourdig;

	if(!strncmp(buff, "0x5545", sizeof("0x5545")-1)){
		nvs->wifi_country_code[0] = 0x45;
		nvs->wifi_country_code[1] = 0x55;
	}
	else if(!strncmp(buff, "0x5355", sizeof("0x5355")-1)){
		nvs->wifi_country_code[0] = 0x55;
		nvs->wifi_country_code[1] = 0x53;
	}
	else{
		printk(KERN_ERR, "===> Error country code! Country code should be 0x5545/0x5355\n");
		return -EFAULT;
	}
		
	goto done;
	
fourdig:
	if(!strncmp(buff, "5545", sizeof("5545")-1)){
		nvs->wifi_country_code[0] = 0x45;
		nvs->wifi_country_code[1] = 0x55;
	}
	else if(!strncmp(buff, "5355", sizeof("5355")-1)){
		nvs->wifi_country_code[0] = 0x55;
		nvs->wifi_country_code[1] = 0x53;
	}
	else{
		printk(KERN_ERR, "===> Error country code! Country code should be 0x5545/0x5355\n");
		return -EFAULT;
	}
	
done:	
	nvs_write();

	return strlen(buff);
}

static void create_wifi_country_code_proc_file(void)
{
	struct proc_dir_entry *proc_file =
		create_proc_entry(PROJ_PROC_WIFI_COUNTRY_CODE, 0666, NULL);

	if (proc_file){
		proc_file->read_proc = wifi_country_code_read_proc;
		proc_file->write_proc = (write_proc_t *)wifi_country_code_write_proc;
	}
	else
		printk(KERN_INFO "proc file create failed!\n");
}

static ssize_t wifi_mac_addr_read_proc(char *page, char **start, off_t off,
		int count, int *eof, void *data){

	if(off > 0){
		*eof = 1;
		return 0;
	}

	nvs_read();
	return sprintf(page, "%s\n", nvs->wifi_mac_addr) + 1;
}

static ssize_t wifi_mac_addr_write_proc(struct file *filp,
		const char *buff, size_t len, loff_t *off)
{
	char messages[WIFI_MAC_ADDR_SIZE] = {0};

	if(len !=  MAC_ADDR_SIZE+1)
		return -EFAULT;

	if (copy_from_user(messages, buff, MAC_ADDR_SIZE))
		return -EFAULT;
	
	messages[MAC_ADDR_SIZE] = 0x0;
	sprintf(nvs->wifi_mac_addr, "%s", messages);
	nvs_write();

	return strlen(buff);
}

static void create_wifi_mac_addr_proc_file(void)
{
	struct proc_dir_entry *proc_file =
		create_proc_entry(PROJ_PROC_WIFI_MAC_ADDR, 0666, NULL);

	if (proc_file){
		proc_file->read_proc = wifi_mac_addr_read_proc;
		proc_file->write_proc = (write_proc_t *)wifi_mac_addr_write_proc;
	}
	else
		printk(KERN_INFO "proc file create failed!\n");
}

static ssize_t bt_mac_addr_read_proc(char *page, char **start, off_t off,
		int count, int *eof, void *data){

	if(off > 0){
		*eof = 1;
		return 0;
	}

	nvs_read();
	return sprintf(page, "%s\n", nvs->bt_mac_addr) + 1;
}

static ssize_t bt_mac_addr_write_proc(struct file *filp,
		const char *buff, size_t len, loff_t *off)
{
	char messages[BT_MAC_ADDR_SIZE] = {0};

	if(len !=  MAC_ADDR_SIZE+1)
		return -EFAULT;

	if (copy_from_user(messages, buff, MAC_ADDR_SIZE))
		return -EFAULT;
	
	messages[MAC_ADDR_SIZE] = 0x0;
	sprintf(nvs->bt_mac_addr, "%s", messages);
	nvs_write();

	return strlen(buff);
}

static void create_bt_mac_addr_proc_file(void)
{
	struct proc_dir_entry *proc_file =
		create_proc_entry(PROJ_PROC_BT_MAC_ADDR, 0666, NULL);

	if (proc_file){
		proc_file->read_proc = bt_mac_addr_read_proc;
		proc_file->write_proc = (write_proc_t *)bt_mac_addr_write_proc;
	}
	else
		printk(KERN_INFO "proc file create failed!\n");
}

static ssize_t acer_code_read_proc(char *page, char **start, off_t off,
		int count, int *eof, void *data){

	if(off > 0){
		*eof = 1;
		return 0;
	}

	nvs_read();
	return sprintf(page, "%s\n", nvs->acer_code) + 1;
}

static ssize_t acer_code_write_proc(struct file *filp,
		const char *buff, size_t len, loff_t *off)
{
	char messages[ACER_CODE_SIZE] = {0};

	if(len !=  ACER_CODE_REAL_SIZE+1)
		return -EFAULT;

	if (copy_from_user(messages, buff, ACER_CODE_REAL_SIZE))
		return -EFAULT;
	
	messages[ACER_CODE_REAL_SIZE] = 0x0;
	sprintf(nvs->acer_code, "%s", messages);
	nvs_write();

	return strlen(buff);
}

static void create_acer_code_proc_file(void)
{
	struct proc_dir_entry *proc_file =
		create_proc_entry(PROJ_PROC_ACER_CODE, 0666, NULL);

	if (proc_file){
		proc_file->read_proc = acer_code_read_proc;
		proc_file->write_proc = (write_proc_t *)acer_code_write_proc;
	}
	else
		printk(KERN_INFO "proc file create failed!\n");
}

static ssize_t gps_sku_read_proc(char *page, char **start, off_t off,
		int count, int *eof, void *data){

	static int init = 0;
	int gps_sku = 0;

	if(off > 0){
		*eof = 1;
		return 0;
	}

	if(!init){
		mt_set_gpio_mode(GPIO74, GPIO_MODE_00);
		mt_set_gpio_dir(GPIO74, GPIO_DIR_IN);
		mt_set_gpio_pull_enable(GPIO74, GPIO_PULL_DISABLE);
	
		msleep(100);
		init = 1;
	}

	gps_sku = mt_get_gpio_in(GPIO74);
	if(gps_sku)
		sprintf(nvs->gps_sku, "%s", "520T+MT3332");
	else
		sprintf(nvs->gps_sku, "%s", "NH520");

	nvs_write();
		
	return sprintf(page, "%s\n", nvs->gps_sku) + 1;
}

static void create_gps_sku_proc_file(void)
{
	struct proc_dir_entry *proc_file =
		create_proc_entry(PROJ_PROC_GPS_SKU, 0666, NULL);

	if (proc_file)
		proc_file->read_proc = gps_sku_read_proc;
	else
		printk(KERN_INFO "proc file create failed!\n");
}

static ssize_t battery_id_read_proc(char *page, char **start, off_t off,
		int count, int *eof, void *data){

	static int init = 0;
	int batt_id1, batt_id2;

	if(off > 0){
		*eof = 1;
		return 0;
	}

	if(!init){
		mt_set_gpio_mode(GPIOEXT31, GPIO_MODE_00);
		mt_set_gpio_dir(GPIOEXT31, GPIO_DIR_IN);
		mt_set_gpio_pull_enable(GPIOEXT31, GPIO_PULL_DISABLE);
		mt_set_gpio_mode(GPIOEXT39, GPIO_MODE_00);
		mt_set_gpio_dir(GPIOEXT39, GPIO_DIR_IN);
		mt_set_gpio_pull_enable(GPIOEXT39, GPIO_PULL_DISABLE);
	
		msleep(100);
		init = 1;
	}

	batt_id1 = mt_get_gpio_in(GPIOEXT31);
	batt_id2 = mt_get_gpio_in(GPIOEXT39);
	if(batt_id1 == 1 && batt_id2 == 1)
		return sprintf(page, "%s\n", "LGC") + 1;
	else if(batt_id1 == 0 && batt_id2 == 1)
		return sprintf(page, "%s\n", "Panasonic") + 1;
	else
		return sprintf(page, "%s\n", "unknown") + 1;
}

static void create_battery_id_proc_file(void)
{
	struct proc_dir_entry *proc_file =
		create_proc_entry(PROJ_PROC_BATTERY_ID, 0666, NULL);

	if (proc_file)
		proc_file->read_proc = battery_id_read_proc;
	else
		printk(KERN_INFO "proc file create failed!\n");
}


static ssize_t psensor_status_read_proc(char *page, char **start, off_t off,
                 int count, int *eof, void *data){
 
         static int init = 0;
         int psensor_status = 0;
 
         if(off > 0){
                 *eof = 1;
                 return 0;
         }
 
         if(!init){
                 mt_set_gpio_mode(GPIO38, GPIO_MODE_00);
                 mt_set_gpio_dir(GPIO38, GPIO_DIR_IN);
                 mt_set_gpio_pull_enable(GPIO38, GPIO_PULL_DISABLE);
 
                 msleep(100);
                 init = 1;
         }
 
         psensor_status = mt_get_gpio_in(GPIO38);
         if(psensor_status)
                 sprintf(nvs->psensor_status, "%s", "1");
         else
                 sprintf(nvs->psensor_status, "%s", "0");
         
         nvs_write();

         return sprintf(page, "%s\n", nvs->psensor_status) + 1;
}

static void create_psensor_status_proc_file(void)
{
        struct proc_dir_entry *proc_dir;
	struct proc_dir_entry *proc_file;
        static int created = 0;
        
	if(created)
		goto end;

	if (!(proc_dir = proc_mkdir("sysinfo/psensor", NULL))) {
                printk(KERN_ERR "--> %d %s %s\n", __LINE__, __func__, __FILE__);
		
		return -1;
	}
	else
		created = 1;

                proc_file = create_proc_entry("sysinfo/psensor/status", 0666, NULL);
                
         if (proc_file)
                 proc_file->read_proc = psensor_status_read_proc;
         else
                 printk(KERN_INFO "proc file create failed!\n");

end:
	return 1;
 }

void wistron_bsp_interface(void){

//	create_proc_dir(PROJ_PROC_INFO_DIR);

	create_ubootversion_proc_file();
	create_osversion_proc_file();
	create_manufacturer_proc_file();
	create_serial_mb_proc_file();
	create_serial_sys_proc_file();
	create_imei_proc_file();
	create_pcb_version_proc_file();
	create_rf_version_proc_file();
	create_wifi_country_code_proc_file();
	create_wifi_mac_addr_proc_file();
	create_bt_mac_addr_proc_file();
	create_acer_code_proc_file();
	create_gps_sku_proc_file();
	create_battery_id_proc_file();
	create_psensor_status_proc_file();
}


void LTE_power_init(void)
{
	//RF_LTE_RESET
	mt_set_gpio_mode(GPIOEXT18, GPIO_MODE_00);
	mt_set_gpio_dir(GPIOEXT18, GPIO_DIR_OUT);
	mt_set_gpio_out(GPIOEXT18, GPIO_OUT_ZERO);

	//RF_LTE_GPS_DISABLE
	mt_set_gpio_mode(GPIOEXT19, GPIO_MODE_00);
	mt_set_gpio_dir(GPIOEXT19, GPIO_DIR_OUT);
	mt_set_gpio_out(GPIOEXT19, GPIO_OUT_ZERO);
 
	//RF_LTE_W_DISABLE
	mt_set_gpio_mode(GPIOEXT20, GPIO_MODE_00);
	mt_set_gpio_dir(GPIOEXT20, GPIO_DIR_OUT);
	mt_set_gpio_out(GPIOEXT20, GPIO_OUT_ZERO);
 
	//RF_LTE_POWER_ON_OFF
	mt_set_gpio_mode(GPIOEXT21, GPIO_MODE_00);
        mt_set_gpio_dir(GPIOEXT21, GPIO_DIR_OUT);
	mt_set_gpio_out(GPIOEXT21, GPIO_OUT_ZERO);
 
	mt_set_gpio_out(GPIOEXT18, GPIO_OUT_ONE); //RF_LTE_RESET
	mt_set_gpio_out(GPIOEXT19, GPIO_OUT_ONE); //RF_LTE_GPS_DISABLE
	mt_set_gpio_out(GPIOEXT20, GPIO_OUT_ONE); //RF_LTE_W_DISABLE
	mt_set_gpio_out(GPIOEXT21, GPIO_OUT_ONE); ///RF_LTE_POWER_ON_OFF

	mdelay(100);
	mt_set_gpio_out(GPIOEXT18, GPIO_OUT_ZERO); //RF_LTE_RESET
	mdelay(50);
	mt_set_gpio_out(GPIOEXT18, GPIO_OUT_ONE); //RF_LTE_RESET

}

