extern "C" void _hang();

[[noreturn]] extern "C" void __cxa_pure_virtual() {
	_hang();
}
