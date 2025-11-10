/*
 * interrupts.h
 *
 * Created: 10/11/2025 02:07:55 p. m.
 *  Author: juanc
 */ 

#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#include <avr/io.h>
#include <avr/interrupt.h>

void Interrupts_Init(void);

extern volatile uint8_t int0_occurred;
extern volatile uint8_t int1_occurred;

#endif