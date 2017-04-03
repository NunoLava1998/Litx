#include "stdtyp.h"
#include "stdio.h"

void kmain(void) {
	gdt_install();
	for(;;);
}
