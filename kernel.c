#include "stdtyp.h"
#include "stdio.h"
#include "gdt.h"

void kmain(void) {
	clear_screen();
	gdt_install();
	for(;;);
}