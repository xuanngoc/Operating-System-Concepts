obj-m += birthdayModule.o
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

test:
	sudo dmesg -C
	sudo insmod mymodule.ko
	sudo rmmod mymodule.ko
	dmesg	