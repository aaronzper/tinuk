#include <kernel/drivers/vesa.h>
#include <kernel/bootboot.h>

extern "C" void kmain(BootbootInfo* bootboot, ARGB* fb) {
	VESABuffer v(fb, bootboot->fb_width, bootboot->fb_height);
	
	ARGB red;
	red.red = 255;

	ARGB white;
	white.red = 255;
	white.green = 255;
	white.blue = 255;
	
	ARGB blue;
	blue.blue = 255;

	int width = 1000;
	int bar_height = 40;

	for(int i = 0; i < 13; i++) {
		ARGB color;
		if (i % 2 == 0) {
			color = red;
		}
		else {
			color = white;
		}

		v.box(color, 0, i * bar_height, width, bar_height);
	}

	v.box(blue, 0, 0, width/3, bar_height * 7);
}
