#include <kernel/bootboot.h>
#include <stdint.h>

typedef struct __attribute__((__packed__)) ARGB {
    unsigned char blue;
    unsigned char green;
    unsigned char red;
    unsigned char alpha;
} ARGB;

class VESADriver {
    public:
        VESADriver(ARGB* fb_ptr, uint32_t s, uint32_t w, uint32_t h);
        void crosshair(ARGB color, unsigned int x, unsigned int y);
        void box(ARGB color, unsigned int x, unsigned int y, unsigned int w, unsigned int h);
    private:
        ARGB* fb;
        uint32_t scanline;
        uint32_t width;
        uint32_t height;
};