#include "stdtyp.h"
#include "stdio.h"
#include "gdt.h"

void kmain(void) {
	gdt_install();
	for(;;);
}