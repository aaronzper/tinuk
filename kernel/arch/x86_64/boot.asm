SECTION .text
GLOBAL _start
GLOBAL _hang
EXTERN _init
EXTERN kmain
EXTERN bootboot
EXTERN fb

_start:
	mov rax, 1
	cpuid 		; Call CPUID to get (among other things) the local APIC id for the core
	shr ebx, 24	; Shift the APIC id into BX
	cmp bx, [bootboot + 0xC] ; bootboot.bspid
	jne _hang	; If we're not the boot CPU, hang

	mov rdi, bootboot ; Load bootboot struct as first param to kmain()
	mov rsi, fb ; Load VESA framebuffer addr as second param to kmain()
	call kmain

_hang:
	cli
	hlt
	jmp _hang
