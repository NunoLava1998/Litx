#include "../stdtyp.h"

void memset(void* ptr, int value, size_t size) {
	unsigned char *buf = (unsigned char *)ptr;
	for (size_t i = 0; i < size; i++) {
		buf[i] = (unsigned char)value;
	}
}

struct gdt_table {
	// The limit is 20 bits long. 
	// The base is 32 bits long.
	uint16_t limit; // 0-16 of the limit
	uint16_t base_low; // 0-16 of the base
	uint8_t base_middle; // 16-24 of the base
	uint8_t access_byte; // The access byte.
	uint8_t flags; // 16-20 of the limit and flags
	uint8_t base_high; // Contains 24-32 of the base.
} __attribute__ ((packed));

struct gdtp {
	uint16_t limit;
	uint32_t base;
} __attribute__ ((packed));

struct gdt_table gdt_i[5];
struct gdtp gdtp;

void gdt_set_gate(int num, uint32_t base, uint32_t limit, uint8_t access_byte, uint8_t flags) {
	gdt_i[num].base_low = base;
	gdt_i[num].base_middle = (base >> 16);
	gdt_i[num].base_high = (base >> 24);
	gdt_i[num].limit = limit;
	gdt_i[num].flags = ((limit >> 16) & 0x0F);
	gdt_i[num].flags |= (flags & 0xF0);
	gdt_i[num].access_byte = access_byte;
}

void gdt_install(void) {
	gdtp.limit = (uint16_t)(sizeof(struct gdt_table) * 5) - 1;
	gdtp.base = (uint32_t)&gdt_i;
	gdt_set_gate(0, 0, 0, 0, 0);
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
	gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
	gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);
	__asm__ __volatile__ ("lgdt %0\n\t"
						  "mov $0x10, %%ax\n\t"
						  "mov %%ax, %%ds\n\t"
						  "mov %%ax, %%es\n\t"
						  "ljmp $0x08,$flush\n\t"
						  "flush: ret" : : "m"(gdtp)
						  );
}
