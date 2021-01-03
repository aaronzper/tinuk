#include <kernel/drivers/terminal.h>
#include <kernel/types/color.h>

#pragma once

namespace IO {
	void set_terminal(Terminal* t);
	Terminal* get_terminal();
	void printk(const char* fmt, ...);
}
