SECTION .text
GLOBAL _start
GLOBAL _hang
EXTERN _init
EXTERN kmain

_start:
	;call _init
	call kmain

_hang:
	cli
	hlt
	jmp _hang
