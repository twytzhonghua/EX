KERN_DIR = /work/system/linux-2.6.22.6

all:
	make -C $(KERN_DIR) M=`pwd` modules 

clean:
	make -C $(KERN_DIR) M=`pwd` modules clean
	rm -rf *odules.*
	rm -rf Module.*
	rm -rf *.bak

obj-m	+= key_irq.o
