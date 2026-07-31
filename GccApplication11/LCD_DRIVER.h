/*
 * LCD_DRIVER.h
 *
 * Created: 2026-07-30 7:19:42 PM
 * Author: Mohamed
 */ 

#ifndef LCD_DRIVER_H_
#define LCD_DRIVER_H_

#include "STD_TYPES.h"
#include "GIO_DRIVER.h" // ?? ????? ???? ??? DIO

#ifndef F_CPU
#define F_CPU 8000000UL
#endif
#include <util/delay.h>

/* Function Prototypes */
void lcd_send_command(u8 command);
void lcd_send_data(u8 data);
void lcd_send_string(u8* str);
void lcd_init(void);
void lcd_goto_xy(u8 line, u8 col);

/* Function Implementations */

void lcd_init(void) {
	// ??? ????? ?????? PORTC ?????? ???????? PORTD ?? OUTPUT
	DIO_SetPinDirection(PORT_C, 4, OUTPUT); // RS
	DIO_SetPinDirection(PORT_C, 5, OUTPUT); // RW
	DIO_SetPinDirection(PORT_C, 7, OUTPUT); // E
	DIO_SetPortDirection(PORT_D, OUTPUT);  // Data Port (D0-D7)

	_delay_ms(50);

	lcd_send_command(0x38); // 8-bit mode, 2 lines, 5x7 dots
	_delay_us(50);

	lcd_send_command(0x38);
	_delay_us(50);

	lcd_send_command(0x0C); // Display ON, Cursor OFF
	_delay_us(50);

	lcd_send_command(0x01); // Clear Display
	_delay_ms(2);

	lcd_send_command(0x06); // Entry Mode
}

void lcd_send_command(u8 command) {
	DIO_SetPinValue(PORT_C, 5, LOW); // RW = 0
	DIO_SetPinValue(PORT_C, 4, LOW); // RS = 0 (Command)

	DIO_SetPortValue(PORT_D, command);

	DIO_SetPinValue(PORT_C, 7, HIGH); // Enable Pulse
	_delay_ms(2);
	DIO_SetPinValue(PORT_C, 7, LOW);
	_delay_ms(5);
}

void lcd_send_data(u8 data) {
	DIO_SetPinValue(PORT_C, 5, LOW);  // RW = 0
	DIO_SetPinValue(PORT_C, 4, HIGH); // RS = 1 (Data)

	DIO_SetPortValue(PORT_D, data);

	DIO_SetPinValue(PORT_C, 7, HIGH); // Enable Pulse
	DIO_SetPinValue(PORT_C, 7, LOW);
	_delay_ms(5);
}

void lcd_send_string(u8* str) {
	u8 i = 0;
	while (str[i] != '\0') {
		lcd_send_data(str[i]);
		i++;
	}
}

void lcd_goto_xy(u8 line, u8 col) {
	u8 address = 0;
	if (line == 1) {
		address = 0x80 + col;
	} else if (line == 2) {
		address = 0xC0 + col;
	}
	lcd_send_command(address);
}

#endif /* LCD_DRIVER_H_ */