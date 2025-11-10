/*
 * CFile1.c
 *
 * Created: 10/11/2025 02:03:43 p. m.
 *  Author: juanc
 */ 

#define F_CPU 16000000UL
#include "lcd.h"

// Función para enviar pulso enable
void LCD_PulseEnable(void) {
	LCD_CTRL_PORT |= (1 << LCD_EN);
	_delay_us(1);
	LCD_CTRL_PORT &= ~(1 << LCD_EN);
	_delay_us(100);
}

// Función para escribir 4 bits
void LCD_Write4Bits(uint8_t data) {
	// Los 4 bits superiores van a los pines D4-D7 (Pines PD4-PD7 = Arduino 4-7)
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (data & 0xF0);
	LCD_PulseEnable();
}

// Inicialización del LCD
void LCD_Init(void) {
	// Configurar pines de datos y control como salidas
	LCD_DATA_DDR |= 0xF0;    // PD4-PD7 como salidas
	LCD_CTRL_DDR |= (1 << LCD_RS) | (1 << LCD_RW) | (1 << LCD_EN);
	
	// Esperar a que el LCD se estabilice
	_delay_ms(50);
	
	// Secuencia de inicialización en 4-bit mode
	LCD_CTRL_PORT &= ~(1 << LCD_RS);  // Modo comando
	LCD_CTRL_PORT &= ~(1 << LCD_RW);  // Modo escritura
	
	// Inicialización en 4-bit mode
	LCD_Write4Bits(0x30);
	_delay_ms(5);
	LCD_Write4Bits(0x30);
	_delay_us(150);
	LCD_Write4Bits(0x30);
	_delay_us(150);
	
	// Cambiar a modo 4-bit
	LCD_Write4Bits(0x20);
	_delay_us(150);
	
	// Function set: 4-bit mode, 2 líneas, 5x8 dots
	LCD_Cmd(LCD_CMD_FUNCTION_SET | LCD_4BIT_MODE | LCD_2LINES | LCD_5x8_DOTS);
	_delay_us(150);
	
	// Display control: Display ON, cursor OFF, blink OFF
	LCD_Cmd(LCD_CMD_DISPLAY_CONTROL | LCD_DISPLAY_ON);
	_delay_us(150);
	
	// Clear display
	LCD_Clear();
	
	// Entry mode set: Increment cursor, no shift
	LCD_Cmd(LCD_CMD_ENTRY_MODE_SET | LCD_ENTRY_INCREMENT | LCD_ENTRY_SHIFT_OFF);
	_delay_ms(2);
}

// Enviar comando al LCD
void LCD_Cmd(uint8_t cmd) {
	LCD_CTRL_PORT &= ~(1 << LCD_RS);  // Modo comando
	LCD_CTRL_PORT &= ~(1 << LCD_RW);  // Modo escritura
	
	LCD_Write4Bits(cmd);
	LCD_Write4Bits(cmd << 4);
	
	// Los comandos de clear y home necesitan más tiempo
	if (cmd == LCD_CMD_CLEAR_DISPLAY || cmd == LCD_CMD_RETURN_HOME) {
		_delay_ms(2);
		} else {
		_delay_us(100);
	}
}

// Enviar dato al LCD
void LCD_Data(uint8_t data) {
	LCD_CTRL_PORT |= (1 << LCD_RS);   // Modo dato
	LCD_CTRL_PORT &= ~(1 << LCD_RW);  // Modo escritura
	
	LCD_Write4Bits(data);
	LCD_Write4Bits(data << 4);
	
	_delay_us(100);
}

// Escribir cadena de texto
void LCD_String(const char *str) {
	while (*str) {
		LCD_Data(*str++);
	}
}

// Limpiar display
void LCD_Clear(void) {
	LCD_Cmd(LCD_CMD_CLEAR_DISPLAY);
	_delay_ms(2);
}

// Posicionar cursor
void LCD_SetCursor(uint8_t row, uint8_t col) {
	uint8_t address;
	
	switch (row) {
		case 0:
		address = 0x00 + col;  // Primera línea: 0x00 - 0x27
		break;
		case 1:
		address = 0x40 + col;  // Segunda línea: 0x40 - 0x67
		break;
		default:
		address = 0x00 + col;
	}
	
	LCD_Cmd(LCD_CMD_SET_DDRAM_ADDR | address);
}