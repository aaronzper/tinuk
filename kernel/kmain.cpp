#include <kernel/drivers/vesa.h>
#include <kernel/bootboot.h>
#include <kernel/io.h>
#include <kernel/panic.h>

extern char environment;

extern "C" void kmain(BootbootInfo* bootboot, Color::ARGB* fb, VESA::PSFHeader* psf, const char* environment) {
	VESA::VESABuffer v(fb, bootboot->fb_width, bootboot->fb_height, bootboot->fb_scanline);
	VESA::PSF font(psf);

	Color::ARGB black;
	Color::ARGB white;
	white.red = 255;
	white.green = 255;
	white.blue = 255;

	VESA::VESATerminal term(v, white, black, font);
	IO::set_terminal(&term);

	IO::printk("Initialized VESA terminal\n");
	IO::printk("Number of cores detected: %u\n", bootboot->numcores);

	unsigned int mmap_entries = (bootboot->size - 128) / 16;
	MMapEnt* mmap = &bootboot->mmap;
	size_t total_mem = 0;
	size_t unusable_mem = 0;
	for(unsigned int i = 0; i < mmap_entries; i++) {
		MMapEnt* entry = &mmap[i];
		size_t size = MMapEnt_Size(entry);
		total_mem += size;
		if(!MMapEnt_IsFree(entry)) {
			unusable_mem += size;
		}
	}

	IO::printk("Total memory detected: %u mb\n", total_mem / 1024 / 1024);
	IO::printk("Unusable memory detected: %u kb\n", unusable_mem / 1024);

	kpanic("Test panic");
}
