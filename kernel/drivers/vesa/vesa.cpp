#include <kernel/drivers/vesa.h>

using namespace VESA;
extern unsigned char _binary_kernel_drivers_vesa_font_psf_start;

VESABuffer::VESABuffer(ARGB* fb_ptr, uint32_t w, uint32_t h, uint32_t s) {
	fb = fb_ptr;
	width = w;
	height = h;
	scanline = s;
}

uint32_t VESABuffer::getWidth() {
	return width;	
}

uint32_t VESABuffer::getHeight() {
	return height;
}

uint32_t VESABuffer::getScanline() {
	return scanline;
}

void VESABuffer::crosshair(ARGB color, unsigned int x, unsigned int y) {
	for(unsigned int y_pos = 0; y_pos < height; y_pos++) {
		fb[(width * y_pos) + (y)] = color;
	}

	for(unsigned int x_pos = 0; x_pos < width; x_pos++) {
		fb[(x) * width + x_pos] = color;
	}
}

void VESABuffer::box(ARGB color, unsigned int x, unsigned int y, unsigned int w, unsigned int h) {
	unsigned int max_x = x + w;
	unsigned int max_y = y + h;
	unsigned int orig_x = x;

	for( ; y < max_y; y++) {
		for( ; x < max_x; x++) {
			fb[(width * y) + x] = color;
		}

		x = orig_x;
	}
}

void VESABuffer::drawchar(char c, PSF font, unsigned int cx, unsigned int cy, ARGB fg, ARGB bg) {
	//unsigned char* glyph = font[c];
	auto h = font.header();

	unsigned char *glyph =
		(unsigned char*)&_binary_kernel_drivers_vesa_font_psf_start +
		h.headersize +
		(c>0&&c<h.numglyph?c:0)*h.bytesperglyph;

	unsigned int x = cx * font.width();
	unsigned int y = cy * font.height();
	unsigned int max_x = x + font.width();
	unsigned int max_y = y + font.height();
	auto orig_x = x;

	unsigned int mask;
	for( ; y < max_y; y++) {
		mask = 1 << (font.width() - 1);

		for( ; x < max_x; x++) {
			fb[(width * y) + x] = ((unsigned int)*glyph) & mask ? fg : bg;
			mask >>= 1;
		}

		x = orig_x;
		glyph += font.bytesPerLine();
	}
}
