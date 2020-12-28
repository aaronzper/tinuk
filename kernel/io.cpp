#include <kernel/io.h>

Terminal* term;

void io::set_terminal(Terminal* t) {
	term = t;
}

void io::printk(const char* str) {
	term->write(str);
}
