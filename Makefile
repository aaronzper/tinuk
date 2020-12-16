ARCH := x86_64

CXX := $(ARCH)-elf-g++
AS 	:= nasm

CXXFLAGS?=-g
ASFLAGS?=-g
CPPFLAGS?=

KDIR 	:= kernel
OBJDIR 	:= build

CXXFLAGS += -ffreestanding -mno-red-zone -Wall -Wextra -mcmodel=large
ASFLAGS += -f elf64
CPPFLAGS += -D__is_kernel -I$(OBJDIR)/include
QEMUFLAGS := -cdrom tinuk.img

LIBS := -nostdlib -lgcc

KOBJ := $(subst .cpp,.o,$(shell find $(KDIR) -type f -name "*.cpp"))
KOBJ += $(subst .asm,.o,$(shell find $(KDIR) -type f -name "*.asm"))

all: install

qemu: install
	qemu-system-x86_64 $(QEMUFLAGS) 

qemu-debug: install
	qemu-system-x86_64 $(QEMUFLAGS) -s -S

install: build
	mkdir -p $(OBJDIR)/boot
	cp $(OBJDIR)/kernel.elf $(OBJDIR)/boot/
	mkbootimg bootboot.json tinuk.img

build: headers $(OBJDIR)/kernel.elf

$(OBJDIR)/kernel.elf: $(KOBJ)	
	mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -T $(KDIR)/arch/$(ARCH)/linker.ld -o $@ $(KOBJ) $(LIBS)

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS) $(CPPFLAGS)

%.o: %.asm
	$(AS) $(ASFLAGS) -o $@ $< 

headers:
	mkdir -p $(OBJDIR)/include/
	ln -s $(PWD)/$(KDIR)/include/ $(PWD)/$(OBJDIR)/include/$(KDIR)

clean:
	rm -f -r $(OBJDIR)
	rm -f $(KOBJ)
