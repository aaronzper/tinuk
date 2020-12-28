export ARCH := x86_64

QEMUFLAGS := -cdrom tinuk.img

export OBJDIR := build
export KDIR := kernel

all: install

qemu: install
	qemu-system-$(ARCH) $(QEMUFLAGS) 

qemu-debug: install
	qemu-system-$(ARCH) $(QEMUFLAGS) -s -S

install: build
	mkdir -p $(OBJDIR)/boot
	cp $(OBJDIR)/kernel.elf $(OBJDIR)/boot/
	mkbootimg bootboot.json tinuk.img

build:
	make -f $(KDIR)/Makefile

clean:
	make -f $(KDIR)/Makefile clean
	rm -rf $(OBJDIR)
