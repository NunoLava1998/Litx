#include "stdtyp.h"

#ifndef _GDT_H_
#define _GDT_H_

extern void memset(void*, int, size_t);
extern void gdt_set_gate(int, uint32_t, uint32_t, uint8_t, uint8_t);
extern void gdt_install(void);

#endif /* _GDT_H_ */