#include <stdarg.h>
#include <stdint.h>
#include <kernel/io.h>
#include <kernel/string.h>

Terminal* term;

void IO::set_terminal(Terminal* t) {
	term = t;
}

Terminal* IO::get_terminal() {
	return term;
}

void IO::printk(const char* fmt, ...) {
	va_list args;
	va_start(args, fmt);	

	bool parse = false;
	for(size_t i = 0; i < strlen(fmt); i++) {
		if(fmt[i] == '%' && !parse) {
			parse = true;
			continue;
		}

		if(fmt[i] == 's' && parse) {
			const char* str = va_arg(args, const char*);
			term->write(str, strlen(str));
			parse = false;
			continue;
		}

		if(fmt[i] == 'u' && parse) {
			// Do a uint64 since we dont know how big it'll be
			uint64_t num = va_arg(args, uint64_t);

			if(num == 0) {
				term->write("0", 1);
				continue;
			}

			// Calculate the length of the final number-string
			size_t len = 0;
			for(uint64_t i = num; i != 0; i /= 10) {
				len++;
			}

			char buf[len];
			for(size_t i = 0; num != 0; i++) {
				int rem = num % 10;

				buf[i] = (rem > 9) ? (rem-10) + 'a' : rem + '0'; 
				
				num /= 10;
			}

			// Go backwards thru the buffer (since the above loop produces it backwards) and print each char
			for(size_t i = len - 1; i+1 > 0; i--) {
				term->write(&buf[i], 1);
			}

			parse = false;
			continue;
		}

		term->write(&fmt[i], 1);	
	}
}
