#include <kernel/bootboot.h>
#include <stdint.h>

namespace VESA {
    typedef struct ARGB {
        unsigned char blue;
        unsigned char green;
        unsigned char red;
        unsigned char alpha;
    } __attribute__((__packed__)) ARGB;

    class VESABuffer {
        public:
            VESABuffer(ARGB* fb_ptr, uint32_t w, uint32_t h);
            void crosshair(ARGB color, unsigned int x, unsigned int y);
            void box(ARGB color, unsigned int x, unsigned int y, unsigned int w, unsigned int h);
        private:
            ARGB* fb;
            uint32_t width;
            uint32_t height;
    };
}