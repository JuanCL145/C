/*
 * CFile1.c
 *
 * Created: 10/11/2025 02:01:14 p. m.
 *  Author: juanc
 */ 

#ifndef LCD_H_
#define LCD_H_

#include <avr/io.h>
#include <util/delay.h>

// Definición de pines para Arduino Uno
#define LCD_DATA_PORT PORTD
#define LCD_DATA_DDR  DDRD
#define LCD_DATA_PIN  PIND

#define LCD_CTRL_PORT PORTB
#define LCD_CTRL_DDR  DDRB
#define LCD_RS PB0     // Pin 8 Arduino
#define LCD_RW PB1     // Pin 9 Arduino (puede conectarse a GND si solo escritura)
#define LCD_EN PB2     // Pin 10 Arduino

// Comandos LCD
#define LCD_CMD_CLEAR_DISPLAY    0x01
#define LCD_CMD_RETURN_HOME      0x02
#define LCD_CMD_ENTRY_MODE_SET   0x04
#define LCD_CMD_DISPLAY_CONTROL  0x08
#define LCD_CMD_CURSOR_SHIFT     0x10
#define LCD_CMD_FUNCTION_SET     0x20
#define LCD_CMD_SET_CGRAM_ADDR   0x40
#define LCD_CMD_SET_DDRAM_ADDR   0x80

// Bits para display control
#define LCD_DISPLAY_ON   0x04
#define LCD_CURSOR_ON    0x02
#define LCD_BLINK_ON     0x01

// Bits para entry mode
#define LCD_ENTRY_INCREMENT  0x02
#define LCD_ENTRY_DECREMENT  0x00
#define LCD_ENTRY_SHIFT_ON   0x01
#define LCD_ENTRY_SHIFT_OFF  0x00

// Bits para function set
#define LCD_8BIT_MODE    0x10
#define LCD_4BIT_MODE    0x00
#define LCD_2LINES       0x08
#define LCD_1LINE        0x00
#define LCD_5x10_DOTS    0x04
#define LCD_5x8_DOTS     0x00

void LCD_Init(void);
void LCD_Cmd(uint8_t cmd);
void LCD_Data(uint8_t data);
void LCD_String(const char *str);
void LCD_Clear(void);
void LCD_SetCursor(uint8_t row, uint8_t col);
void LCD_PulseEnable(void);
void LCD_Write4Bits(uint8_t data);

#endif