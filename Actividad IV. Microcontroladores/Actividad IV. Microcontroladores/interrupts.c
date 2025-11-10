/*
 * interrupts.c
 *
 * Created: 10/11/2025 02:08:18 p. m.
 *  Author: juanc
 */ 

#define F_CPU 16000000UL
#include "interrupts.h"
#include "counter.h"
#include "lcd.h"

volatile uint8_t int0_occurred = 0;
volatile uint8_t int1_occurred = 0;

ISR(INT0_vect) {
	int0_occurred = 1;
}

ISR(INT1_vect) {
	int1_occurred = 1;
}

void Interrupts_Init() {
	// Configurar INT0 y INT1 para flanco de subida
	EICRA |= (1 << ISC01) | (1 << ISC00); // INT0 rising edge
	EICRA |= (1 << ISC11) | (1 << ISC10); // INT1 rising edge
	EIMSK |= (1 << INT0) | (1 << INT1);   // Enable INT0 and INT1
	sei();
}