/*
 * CFile1.c
 *
 * Created: 10/11/2025 02:05:18 p. m.
 *  Author: juanc
 */ 

#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>

void ADC_Init(void);
uint16_t ADC_Read(uint8_t channel);
float Read_Temperature(void);

#endif