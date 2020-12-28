CXX := $(ARCH)-elf-g++
AS 	:= nasm
LD := $(ARCH)-elf-ld

CXXFLAGS?=-g -Og
ASFLAGS?=-g
CPPFLAGS?=

CXXFLAGS += -ffreestanding -mno-red-zone -Wall -Wextra -mcmodel=large -fno-exceptions
ASFLAGS += -f elf64
CPPFLAGS += -D__is_kernel -I$(OBJDIR)/include

LIBS := -nostdlib -lgcc

KOBJ := $(subst .cpp,.o,$(shell find $(KDIR) -type f -name "*.cpp"))
KOBJ += $(subst .asm,.o,$(shell find $(KDIR) -type f -name "*.asm"))
KOBJ += $(subst .psf,.o,$(shell find $(KDIR) -type f -name "*.psf"))

all: $(OBJDIR)/kernel.elf

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
	rm -f $(KOBJ)
