KDIR ?= /lib/modules/`uname -r`/build

.PHONY: clean default defconfig all

clean:
	$(MAKE) -C $(KDIR) M=$$PWD clean

default:
	$(MAKE) -C $(KDIR) M=$$PWD

defconfig:

install: all
	sudo rm -f /lib/modules/`uname -r`/kernel/drivers/gpu/drm/panel/panel-friendlyelec.ko.xz
	sudo cp panel-friendlyelec.ko /lib/modules/`uname -r`/kernel/drivers/gpu/drm/panel/
	sudo xz /lib/modules/`uname -r`/kernel/drivers/gpu/drm/panel/panel-friendlyelec.ko
	sudo depmod -A
	sudo armbian-add-overlay k116e.dts
all: default
