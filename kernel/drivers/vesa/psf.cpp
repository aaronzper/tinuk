#include <kernel/drivers/vesa.h>
#include <kernel/panic.h>

using namespace VESA;

PSF::PSF(PSFHeader* h) {
	if(h->magic != PSF_magic) {
		kpanic("Invalid PSF magic value");
	}

	psf_header = h;
}

PSFHeader PSF::header() {
	return *psf_header;
}

unsigned char* PSF::operator[](char c) {
		return (unsigned char*)psf_header +
		psf_header->headersize +
		(c > 0 && (uint32_t)c < psf_header->numglyph ? c : 0) * psf_header->bytesperglyph;
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
