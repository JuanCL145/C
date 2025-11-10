/*
 * Actividad IV. Microcontroladores.c
 *
 * Created: 10/11/2025 01:54:13 p. m.
 * Author : juanc
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "lcd.h"
#include "adc.h"
#include "counter.h"
#include "interrupts.h"

int main(void) {
	LCD_Init();
	ADC_Init();
	Interrupts_Init();

	while (1) {
		// Normal counter operation
		if (display_counter) {
			Counter_UpdateDisplay();
			_delay_ms(100);
			if (counter < 100000) counter++;
		}

		// Temperature check
		float temp = Read_Temperature();
		if (temp > 25.0) {
			display_counter = 0;
			LCD_Clear();
			LCD_String("TEMP ALTA!");
			while (Read_Temperature() > 25.0) {
				_delay_ms(500);
			}
			LCD_Clear();
			display_counter = 1;
		}

		// INT0 handling
		if (int0_occurred) {
			display_counter = 0;
			LCD_Clear();
			LCD_String("INT0 OK");
			_delay_ms(5000);
			LCD_Clear();
			display_counter = 1;
			int0_occurred = 0;
		}

		// INT1 handling
		if (int1_occurred) {
			display_counter = 0;
			LCD_Clear();
			LCD_String("INT1 OK");
			_delay_ms(5000);
			LCD_Clear();
			display_counter = 1;
			int1_occurred = 0;
		}
	}
}
