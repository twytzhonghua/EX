obj-m := i2c_drv_albert.o

KERNELDIR ?= /usr/src/linux-headers-$(shell uname -r)/
PWD := $(shell pwd)

all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules    


clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
	rm -rf .tmp_versions
