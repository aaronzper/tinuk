#include <kernel/drivers/vesa.h>

using namespace VESA;

PSF::PSF(PSFHeader* h) {
    if(psf_header->magic != PSF_magic) {
        // Do something
    }

    psf_header = h;
}

PSFHeader PSF::header() {
    return *psf_header;
}

unsigned char* PSF::operator[](char c) {
    unsigned char* start = (unsigned char*)(psf_header + psf_header->headersize);
    unsigned int index = (c > 0 && c < psf_header->numglyph ? c : 0) * psf_header->bytesperglyph;

    return &(start[index]);
}

unsigned int PSF::bytesPerLine() {
    return (psf_header->width + 7) / 8;
}

unsigned int PSF::height() {
    return psf_header->height;
}

unsigned int PSF::width() {
    return psf_header->width;
}