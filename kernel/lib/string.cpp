#include <stddef.h>
#include <kernel/string.h>

size_t strlen(const char* str) {
	for(size_t i = 0;; i++) {
		if(str[i] == '\0') {
			return i;
		}
	}
}
