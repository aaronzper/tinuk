#include <kernel/io.h>
#include <kernel/string.h>

Terminal* term;

void io::set_terminal(Terminal* t) {
	term = t;
}

void io::printk(const char* str) {
	term->write(str, strlen(str));
}
