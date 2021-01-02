CXX := clang++ -target $(ARCH)-pc-none-elf
AS  := nasm
LD  := ld

CXXFLAGS?=-g -Og
ASFLAGS?=-g -F dwarf
CPPFLAGS?=

CXXFLAGS += -ffreestanding -mno-red-zone -Wall -Wextra -mcmodel=large -fno-exceptions -fno-rtti
ASFLAGS += -f elf64
CPPFLAGS += -D__is_kernel -I$(OBJDIR)/include

LIBS := -nostdlib

KOBJ := $(subst .cpp,.o,$(shell find $(KDIR) -type f -name "*.cpp" -not -path "$(KDIR)/arch/*"))
KOBJ += $(subst .asm,.o,$(shell find $(KDIR) -type f -name "*.asm" -not -path "$(KDIR)/arch/*"))
KOBJ += $(subst .bin,.o,$(shell find $(KDIR) -type f -name "*.bin" -not -path "$(KDIR)/arch/*"))

KARCHOBJ := $(subst .cpp,.o,$(shell find $(KDIR)/arch/$(ARCH)/ -type f -name "*.cpp"))
KARCHOBJ += $(subst .asm,.o,$(shell find $(KDIR)/arch/$(ARCH)/ -type f -name "*.asm"))

.PHONY: all headers clean

all: $(OBJDIR)/kernel.elf

$(OBJDIR)/kernel.elf: headers $(KOBJ) $(KARCHOBJ)
	@mkdir -p $(OBJDIR)
	@echo Linking kernel
	@$(CXX) $(CXXFLAGS) -T $(KDIR)/arch/$(ARCH)/linker.ld -o $@ $(KOBJ) $(KARCHOBJ) $(LIBS)

%.o: %.cpp
	@echo CXX $<
	@$(CXX) -c $< -o $@ $(CXXFLAGS) $(CPPFLAGS)

%.o: %.asm
	@echo AS $<
	@$(AS) $(ASFLAGS) -o $@ $< 

%.o: %.bin
	@echo LD $<
	@$(LD) -r -b binary -o $@ $<

headers:
	@mkdir -p $(OBJDIR)/include/
	@echo Making symlink to kernel headers
	@ln -s -f $(PWD)/$(KDIR)/include/ $(PWD)/$(OBJDIR)/include/$(KDIR)
	@rm -f $(KDIR)/include/include # If there's already a symlink for build/include/kernel it'll make another one in kernel/include, so delete it if that happens

clean:
	@echo Cleaning kernel objects
	@rm -f $(KOBJ) $(KARCHOBJ)
