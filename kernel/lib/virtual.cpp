extern "C" void _hang();

extern "C" void __cxa_pure_virtual() {
	_hang();
}
