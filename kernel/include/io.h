#include <kernel/drivers/terminal.h>

#pragma once

namespace io {
	void set_terminal(Terminal* t);
	void printk(const char* str);
}
