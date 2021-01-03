#include <stdint.h>

#pragma once

namespace Color {
	typedef struct ARGB {
		uint8_t blue;
		uint8_t green;
		uint8_t red;
		uint8_t alpha;
	} __attribute__((__packed__)) ARGB;
}
