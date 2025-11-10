/*
 * CFile1.c
 *
 * Created: 10/11/2025 02:05:56 p. m.
 *  Author: juanc
 */ 

#define F_CPU 16000000UL
#include "adc.h"

void ADC_Init() {
	ADMUX = (1 << REFS0); // AVcc as reference
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Enable ADC, prescaler 128
}

uint16_t ADC_Read(uint8_t channel) {
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
	ADCSRA |= (1 << ADSC);
	while (ADCSRA & (1 << ADSC));
	return ADC;
}

float Read_Temperature() {
	uint16_t adc_value = ADC_Read(0); // Assuming LM35 on channel 0
	float voltage = (adc_value * 5.0) / 1024.0;
	return voltage * 100.0; // LM35: 10mV/°C
}