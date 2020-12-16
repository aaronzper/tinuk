SECTION .text
GLOBAL _start
GLOBAL _hang
EXTERN _init
EXTERN kmain
EXTERN bootboot
EXTERN fb

_start:
	mov rdi, bootboot ; Load bootboot struct as first param to kmain()
	mov rsi, fb ; Load VESA framebuffer addr as second param to kmain()
	call kmain

_hang:
	cli
	hlt
	jmp _hang
