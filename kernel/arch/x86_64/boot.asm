SECTION .text
GLOBAL _start
GLOBAL _hang
EXTERN kmain
EXTERN bootboot
EXTERN fb
EXTERN _binary_kernel_drivers_vesa_font_bin_start
EXTERN environment

_start:
	mov rax, 1
	cpuid 		; Call CPUID to get (among other things) the local APIC id for the core
	shr ebx, 24	; Shift the APIC id into BX
	cmp bx, [bootboot + 0xC] ; bootboot.bspid
	jne _hang	; If we're not the boot CPU, hang

	mov rdi, bootboot ; Load pointer to bootboot struct as first param to kmain()
	mov rsi, fb ; Load pointer to VESA framebuffer as second param to kmain()
	mov rdx, _binary_kernel_drivers_vesa_font_bin_start ; Load pointer to PSF header as third param to kmain()
	mov rcx, environment ; Load pointer to environment string as fourth param to kmain()
	call kmain

_hang:
	cli
	hlt
	jmp _hang
