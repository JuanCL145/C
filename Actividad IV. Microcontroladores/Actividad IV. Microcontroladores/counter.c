/*
 * counter.c
 *
 * Created: 10/11/2025 02:07:01 p. m.
 *  Author: juanc
 */ 

#define F_CPU 16000000UL
#include "counter.h"
#include "lcd.h"
#include <stdio.h>

uint32_t counter = 0;
uint8_t display_counter = 1; // 1 = show counter, 0 = show message

void Counter_UpdateDisplay() {
	if (display_counter) {
		LCD_SetCursor(0, 0);
		LCD_String("CONTADOR");
		LCD_SetCursor(1, 0);
		char buffer[16];
		sprintf(buffer, "%lu", counter);
		LCD_String(buffer);
	}
}