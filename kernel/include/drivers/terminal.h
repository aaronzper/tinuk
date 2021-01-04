#include <stddef.h>
#include <kernel/types/color.h>

#pragma once

class Terminal {
	public:
		virtual void write(const char* str, size_t len) = 0;
		virtual void set_fg(const Color::ARGB& fg) = 0;
		virtual void set_bg(const Color::ARGB& bg) = 0;
		virtual void set_pos(unsigned int x_pos, unsigned int y_pos) = 0;
};
