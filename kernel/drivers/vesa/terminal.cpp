#include <kernel/drivers/vesa.h>

using namespace VESA;

VESATerminal::VESATerminal(VESABuffer _buf, ARGB _fg, ARGB _bg, PSF _font) : buf(_buf), font(_font) {
	fg = _fg;
	bg = _bg;
}

void VESATerminal::write(const char* str) {
	static unsigned int line = 0;
	static unsigned int x = 0;
	for(int i = 0; str[i] != '\0'; i++) {
		if(str[i] == '\n') {
			x = 0;
			line++;
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