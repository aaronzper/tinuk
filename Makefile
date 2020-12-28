export ARCH := x86_64

QEMUFLAGS := -cdrom tinuk.img

export OBJDIR := build
export KDIR := kernel

all: install

qemu: install
	qemu-system-$(ARCH) $(QEMUFLAGS) 

qemu-debug: install
	qemu-system-$(ARCH) $(QEMUFLAGS) -s -S

install: $(OBJDIR)/kernel.elf
	mkdir -p $(OBJDIR)/boot
	cp $< $(OBJDIR)/boot/
	mkbootimg bootboot.json tinuk.img

$(OBJDIR)/kernel.elf:
	$(MAKE) -f $(KDIR)/Makefile $@

clean:
	$(MAKE) -f $(KDIR)/Makefile clean
	rm -rf $(OBJDIR)
