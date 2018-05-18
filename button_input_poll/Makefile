ifneq ($(KERNELRELEASE),)

obj-m := key.o

else

	KDIR=/home/qwc/workdir/mcsdk/mcsdk_1_01_00_02/board-support/linux-3.3-psp03.22.00.06.sdk 
all:
	make -C $(KDIR) M=$(PWD) modules ARCH=arm CROSS_COMPILE=arm-arago-linux-gnueabi-

clean:
	rm -rf *.ko *.o *.mod.o *.mod.c *.symvers  modul* .button.* .tmp_versions
#help: make KDIR=<you kernel path>
endif
