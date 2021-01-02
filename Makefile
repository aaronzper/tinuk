export ARCH := x86_64

export OBJDIR := build
export KDIR := kernel

QEMUFLAGS := -cdrom tinuk.img -smp 8

.PHONY: all qemu qemu-debug install kernel clean

all: install

qemu: install
	@echo Running QEMU
	@qemu-system-$(ARCH) $(QEMUFLAGS) 

qemu-debug: install
	@echo Running QEMU listening for GDB
	@qemu-system-$(ARCH) $(QEMUFLAGS) -s -S

install: kernel
	@mkdir -p $(OBJDIR)/boot
	@cp $(OBJDIR)/kernel.elf $(OBJDIR)/boot/
	@echo Making kernel image with BOOTBOOT
	@mkbootimg bootboot.json tinuk.img

kernel:
	@echo Making kernel
	@$(MAKE) -f $(KDIR)/Makefile

clean:
	@$(MAKE) -f $(KDIR)/Makefile clean
	@echo Cleaning build directory
	@rm -rf $(OBJDIR)
