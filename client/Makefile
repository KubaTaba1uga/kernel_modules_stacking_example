PWD   := $(shell pwd)
KDIR  := /lib/modules/$(shell uname -r)/build/
obj-m += client_lkm.o

ccflags-y += -DDEBUG

all:
	make -C $(KDIR) M=$(PWD) KBUILD_EXTRA_SYMBOLS=$(PWD)/../core/Module.symvers modules 
install:
	make -C $(KDIR) M=$(PWD) modules_install
clean:
	make -C $(KDIR) M=$(PWD) clean
