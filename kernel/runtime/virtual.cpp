#include <kernel/panic.h>

[[noreturn]] extern "C" void __cxa_pure_virtual() {
	kpanic("Pure virtual function called");
}
