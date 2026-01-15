ifneq ($(KERNELRELEASE),)
# Додаємо налагоджувальну інформацію
ccflags-y += -g
obj-m := hello.o
else
KDIR ?= /lib/modules/`uname -r`/build

default:
	$(MAKE) -C $(KDIR) M=$$PWD
clean:
	$(MAKE) -C $(KDIR) M=$$PWD clean
endif
