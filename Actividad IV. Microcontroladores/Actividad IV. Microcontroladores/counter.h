/*
 * CFile1.c
 *
 * Created: 10/11/2025 02:06:25 p. m.
 *  Author: juanc
 */ 

#ifndef COUNTER_H_
#define COUNTER_H_

#include <stdint.h>

extern uint32_t counter;
extern uint8_t display_counter;

void Counter_UpdateDisplay(void);

#endif