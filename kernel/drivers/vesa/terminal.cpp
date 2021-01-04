#include <kernel/drivers/vesa.h>
#include <kernel/string.h>

using namespace VESA;

VESATerminal::VESATerminal(VESABuffer _buf, Color::ARGB _fg, Color::ARGB _bg, PSF _font) : buf(_buf), font(_font) {
	fg = _fg;
	bg = _bg;

	x = 0;
	line = 0;
}

void VESATerminal::write(const char* str, size_t len) {
	for(size_t i = 0; i < len; i++) {
		if(str[i] == '\n') {
			x = 0;
			line++;
			continue;
		}

		if(str[i] == '\t') {
			const uint8_t tabwidth = 8;
			unsigned int offset = tabwidth - (x % tabwidth);
			if (offset == 0) offset = tabwidth;

			x += offset;
			continue;
		}

		buf.drawchar(str[i], font, x, line, fg, bg);
		x++;
		if(x >= buf.getWidth()/8) {
			x = 0;
			line++;
		}
	}
}

void VESATerminal::set_fg(const Color::ARGB& _fg) {
	fg = _fg;
}

void VESATerminal::set_bg(const Color::ARGB& _bg) {
	bg = _bg;
}

void VESATerminal::set_pos(unsigned int x_pos, unsigned int y_pos) {
	x = x_pos;
	line = y_pos;
}
