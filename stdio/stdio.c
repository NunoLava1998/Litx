#include "../stdtyp.h" // Include types (like uint16_t, int32_t, etc.)
#include "../stdio.h"

uint8_t x = 0;
uint8_t y = 0;
uint16_t* vptr = (uint16_t*)0xB8000;

const int vga_height = 25;
const int vga_width = 80;
const int vga_h_minus_one = 24;
const int vga_w_minus_one = 79;

void _scroll(void) {
	// _scroll(); is a function that scrolls the screen.
	for (int yf = 1; yf < vga_height; yf++) {
		for (int xf = 0; xf < vga_width; xf++) {
			vptr[yf * vga_width + xf] = vptr[(yf - 1) * vga_width + xf];
		}
	}
	// We should clear the last line with zeroes.
	for (int xf = 0; xf < vga_width; xf++) {
		vptr[vga_height * vga_width + xf] = (uint16_t)0x0000;
	}
	// Now we should update the position.
	x = 0;
	y = (int)vga_h_minus_one;
}

size_t _strlen(const char* string) {
	size_t len = 0;
	while (string[len] != '\0') {
		len++;
	}
	return len;
}

void printc(byte character, uint8_t color_bc, uint8_t color_fc) {
	if (x >= vga_width && y >= vga_height) {
		_scroll();
	}
	// In case the character is a newline...
	if (character == '\n') {
		if (x >= vga_width && y >= vga_height) {
			// We don't want to scroll into other pages.
			_scroll();
			return;
		} else {
			y++;
			x = 0;
			return;
		}
		return;
	}
	// In case the character is a backspace...
	if (character == '\b') {
		if (x == 0 && y == 0) {
			vptr[y * vga_width + x] = ' ' | (((0 << 4) | (0 & 0x0F)) << 8);
			x = (int)vga_w_minus_one;
			y = (int)vga_h_minus_one;
			return;
		} else if (x == 0) {
			vptr[y * vga_width + x] = ' ' | (((0 << 4) | (0 & 0x0F)) << 8);
			x = 0;
			y--;
			return;
		} else {
			vptr[y * vga_width + x] = ' ' | (((0 << 4) | (0 & 0x0F)) << 8);
			x--;
			return;
		}
		return;
	}
	// Now for the actual printing...
	uint8_t color_var = (uint8_t)((color_bc << 4) | (color_fc | 0x0F));
	uint16_t _character = character | (color_var << 8);
	vptr[y * vga_width + x] = _character;
	if (x == vga_width) {
		x = 0;
		y++;
		return;
	} else {
		x++;
		return;
	}
	return;
}

void prints(const char* string, uint8_t color_bc, uint8_t color_fc) {
	for (size_t i = 0; i < _strlen(string); i++) {
			printc(string[i], color_bc, color_fc);
	}
	return;
}
