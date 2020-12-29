#include <kernel/drivers/terminal.h>

#pragma once

namespace IO {
	void set_terminal(Terminal* t);
	void printk(const char* fmt, ...);
}
