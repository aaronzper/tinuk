CXX := $(ARCH)-elf-g++
AS 	:= nasm
LD	:= $(ARCH)-elf-ld

CXXFLAGS?=-g -Og
ASFLAGS?=-g
CPPFLAGS?=

CXXFLAGS += -ffreestanding -mno-red-zone -Wall -Wextra -mcmodel=large -fno-exceptions -fno-rtti
ASFLAGS += -f elf64
CPPFLAGS += -D__is_kernel -I$(OBJDIR)/include

LIBS := -nostdlib -lgcc

KOBJ := $(subst .cpp,.o,$(shell find $(KDIR) -type f -name "*.cpp" -not -path "$(KDIR)/arch/*"))
KOBJ += $(subst .asm,.o,$(shell find $(KDIR) -type f -name "*.asm" -not -path "$(KDIR)/arch/*"))
KOBJ += $(subst .psf,.o,$(shell find $(KDIR) -type f -name "*.psf" -not -path "$(KDIR)/arch/*"))

KARCHOBJ := $(subst .cpp,.o,$(shell find $(KDIR)/arch/$(ARCH)/ -type f -name "*.cpp"))
KARCHOBJ += $(subst .asm,.o,$(shell find $(KDIR)/arch/$(ARCH)/ -type f -name "*.asm"))

.PHONY: all headers clean

all: $(OBJDIR)/kernel.elf

$(OBJDIR)/kernel.elf: headers $(KOBJ) $(KARCHOBJ)
	mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -T $(KDIR)/arch/$(ARCH)/linker.ld -o $@ $(KOBJ) $(KARCHOBJ) $(LIBS)

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
	rm -f $(KOBJ) $(KARCHOBJ)
