ARCH := x86_64

CXX := $(ARCH)-elf-g++
AS 	:= nasm
LD := $(ARCH)-elf-ld

CXXFLAGS?=-g
ASFLAGS?=-g
CPPFLAGS?=

KDIR 	:= kernel
OBJDIR 	:= build

CXXFLAGS += -ffreestanding -mno-red-zone -Wall -Wextra -mcmodel=large -fno-exceptions
ASFLAGS += -f elf64
CPPFLAGS += -D__is_kernel -I$(OBJDIR)/include
QEMUFLAGS := -cdrom tinuk.img

LIBS := -nostdlib -lgcc

KOBJ := $(subst .cpp,.o,$(shell find $(KDIR) -type f -name "*.cpp"))
KOBJ += $(subst .asm,.o,$(shell find $(KDIR) -type f -name "*.asm"))
KOBJ += $(subst .psf,.o,$(shell find $(KDIR) -type f -name "*.psf"))

all: install

qemu: install
	qemu-system-$(ARCH) $(QEMUFLAGS) 

qemu-debug: install
	qemu-system-$(ARCH) $(QEMUFLAGS) -s -S

install: build
	mkdir -p $(OBJDIR)/boot
	cp $(OBJDIR)/kernel.elf $(OBJDIR)/boot/
	mkbootimg bootboot.json tinuk.img

build: $(OBJDIR)/kernel.elf

$(OBJDIR)/kernel.elf: headers $(KOBJ)	
	mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -T $(KDIR)/arch/$(ARCH)/linker.ld -o $@ $(KOBJ) $(LIBS)

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS) $(CPPFLAGS)

%.o: %.asm
	$(AS) $(ASFLAGS) -o $@ $< 

%.o: %.psf
	$(LD) -r -b binary -o $@ $<

headers:
	mkdir -p $(OBJDIR)/include/
	ln -s -f $(PWD)/$(KDIR)/include/ $(PWD)/$(OBJDIR)/include/$(KDIR)
	rm -f $(KDIR)/include/include # If there's already a symlink for build/include/kernel it'll make another one in kernel/include, so delete it if that happens

clean:
	rm -f -r $(OBJDIR)
	rm -f $(KOBJ)
