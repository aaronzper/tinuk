#include <kernel/bootboot.h>
#include <stdint.h>
#include <kernel/drivers/terminal.h>

#pragma once

namespace VESA {
    const uint32_t PSF_magic = 0x864ab572;

    typedef struct {
        uint32_t magic;         // Should equal PSF_magic
        uint32_t version;       // Zero
        uint32_t headersize;    // Offset of bitmaps in file
        uint32_t flags;         // Zero if there isnt a unicode table
        uint32_t numglyph;      // Num. of glyphs
        uint32_t bytesperglyph; // Size of each glyph in bytes
        uint32_t height;        // Glyph height in pixels
        uint32_t width;         // Glyph width in pixels
    } PSFHeader;

    typedef struct ARGB {
        uint8_t blue;
        uint8_t green;
        uint8_t red;
        uint8_t alpha;
    } __attribute__((__packed__)) ARGB;

    class PSF {
        public:
            PSF(PSFHeader* h);
            PSFHeader header();
            unsigned char* operator[](char c);
            unsigned int bytesPerLine();
            unsigned int height();
            unsigned int width();
        private:
            PSFHeader* psf_header;
    };

    class VESABuffer {
        public:
            VESABuffer(ARGB* fb_ptr, uint32_t w, uint32_t h, uint32_t s);

			uint32_t getWidth();
			uint32_t getHeight();
			uint32_t getScanline();

            void crosshair(ARGB color, unsigned int x, unsigned int y);
            void box(ARGB color, unsigned int x, unsigned int y, unsigned int w, unsigned int h);
            void drawchar(char c, PSF font, unsigned int cx, unsigned int cy, ARGB fg, ARGB bg);

        private:
            ARGB* fb;
            uint32_t width;
            uint32_t height;
            uint32_t scanline;
    };

	class VESATerminal : public Terminal {
		public:
			VESATerminal(VESABuffer _buf, ARGB _fg, ARGB _bg, PSF _font);
			void write(const char* str) override;

		private:
			VESABuffer buf;	
			ARGB fg;
			ARGB bg;
			PSF font;
	};
}
