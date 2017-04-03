#ifndef _STDIO_H_LITX_
#define _STDIO_H_LITX_

extern uint8_t x;
extern uint8_t y;
extern uint16_t* vptr;
extern void _scroll(void);
extern size_t _strlen(const char*);
extern void printc(byte, uint8_t, uint8_t);
extern void prints(const char*, uint8_t, uint8_t);
extern void clear_screen(void);

#endif /* _STDIO_H_LITX_ */ 