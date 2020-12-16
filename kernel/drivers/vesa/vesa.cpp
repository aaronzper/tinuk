#include <kernel/drivers/vesa.h>

using namespace VESA;

VESABuffer::VESABuffer(ARGB* fb_ptr, uint32_t w, uint32_t h) {
    fb = fb_ptr;
    width = w;
    height = h;
}

void VESABuffer::crosshair(ARGB color, unsigned int x, unsigned int y) {
    for(unsigned int y_pos = 0; y_pos < height; y_pos++) {
        fb[(width * y_pos) + (y)] = color;
    }

    for(unsigned int x_pos = 0; x_pos < width; x_pos++) {
        fb[(x) * width + x_pos] = color;
    }
}

void VESABuffer::box(ARGB color, unsigned int x, unsigned int y, unsigned int w, unsigned int h) {
    unsigned int max_x = x + w;
    unsigned int max_y = y + h;
    unsigned int orig_x = x;

    for( ; y < max_y; y++) {
        for( ; x < max_x; x++) {
            fb[(width * y) + x] = color;
        }

        x = orig_x;
    }
}