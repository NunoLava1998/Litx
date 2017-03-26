#include "stdtyp.h"
#include "stdio.h"

void kmain(void) {
	prints("Hello, World!", BLACK, WHITE);
	// Nothing to do for now.
	for(;;) {
		__asm__ __volatile__("hlt");
	}
}