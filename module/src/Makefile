KERNEL_SOURCE ?= /lib/modules/$(shell uname -r)/build
# EXTRA_CFLAGS += -DDEBUG

obj-m += semstate.o

all:
	$(MAKE) -C $(KERNEL_SOURCE)  M=$(PWD) modules

clean:
	$(MAKE) -C $(KERNEL_SOURCE) M=$(PWD) clean
