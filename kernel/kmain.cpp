#include <kernel/drivers/vesa.h>
#include <kernel/bootboot.h>
#include <kernel/io.h>

extern char environment;

extern "C" void kmain(BootbootInfo* bootboot, VESA::ARGB* fb, VESA::PSFHeader* psf) {
	VESA::VESABuffer v(fb, bootboot->fb_width, bootboot->fb_height, bootboot->fb_scanline);
	VESA::PSF font(psf);

	VESA::ARGB black;
	VESA::ARGB white;
	white.red = 255;
	white.green = 255;
	white.blue = 255;

	VESA::VESATerminal term(v, white, black, font);
	io::set_terminal(&term);

	io::printk("Initialized VESA terminal");
}
