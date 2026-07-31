/*
 * KEPAD_DRIVER.h
 *
 * Created: 2026-07-30 7:31:12 PM
 * Author: Mohamed
 */ 

#ifndef KEPAD_DRIVER_H_
#define KEPAD_DRIVER_H_

#include "STD_TYPES.h"
#include "GIO_DRIVER.h"  // ????? ???? ??? DIO

#ifndef F_CPU
#define F_CPU 8000000UL
#endif
#include <util/delay.h>

#include "LCD_DRIVER.h"  // ????? ???? ??? LCD ???? ???? Get_Number_From_Keypad

#define NOT_PRESSED 0xFF

/* Function Prototypes */
void KEYPAD_Init(void);
u8 PressedKey(void);
u16 Get_Number_From_Keypad(void);
void NumberToString(u8 num, u8* str);

const u8 Keypad_Buttons[4][4] = {
	{'7', '8', '9', '/'},
	{'4', '5', '6', '*'},
	{'1', '2', '3', '-'},
	{'C', '0', '=', '+'}
};

void NumberToString(u8 num, u8* str) {
	u8 i = 0;
	u8 temp[10];
	u8 j = 0;

	if (num == 0) {
		str[0] = '0';
		str[1] = '\0';
		return;
	}

	while (num > 0) {
		temp[i++] = (num % 10) + '0';
		num /= 10;
	}

	while (i > 0) {
		str[j++] = temp[--i];
	}
	str[j] = '\0';
}

void KEYPAD_Init(void) {
	DIO_SetPinDirection(PORT_A, 3, OUTPUT);
	DIO_SetPinDirection(PORT_A, 4, OUTPUT);
	DIO_SetPinDirection(PORT_A, 5, OUTPUT);
	DIO_SetPinDirection(PORT_A, 6, OUTPUT);

	DIO_SetPinValue(PORT_A, 3, HIGH);
	DIO_SetPinValue(PORT_A, 4, HIGH);
	DIO_SetPinValue(PORT_A, 5, HIGH);
	DIO_SetPinValue(PORT_A, 6, HIGH);

	DIO_SetPinDirection(PORT_B, 4, INPUT);
	DIO_SetPinDirection(PORT_B, 5, INPUT);
	DIO_SetPinDirection(PORT_B, 6, INPUT);
	DIO_SetPinDirection(PORT_B, 7, INPUT);

	DIO_SetPinValue(PORT_B, 4, HIGH);
	DIO_SetPinValue(PORT_B, 5, HIGH);
	DIO_SetPinValue(PORT_B, 6, HIGH);
	DIO_SetPinValue(PORT_B, 7, HIGH);
}

u8 PressedKey(void) {
	u8 key = NOT_PRESSED;
	u8 row_pins[4] = {3, 4, 5, 6};
	u8 col_pins[4] = {4, 5, 6, 7};

	for (u8 r = 0; r < 4; r++) {
		DIO_SetPinValue(PORT_A, row_pins[r], LOW);

		for (u8 c = 0; c < 4; c++) {
			if (DIO_GetPinValue(PORT_B, col_pins[c]) == LOW) {
				_delay_ms(30);
				while (DIO_GetPinValue(PORT_B, col_pins[c]) == LOW);
				
				key = Keypad_Buttons[r][c];
				break;
			}
		}

		DIO_SetPinValue(PORT_A, row_pins[r], HIGH);

		if (key != NOT_PRESSED) {
			break;
		}
	}

	return key;
}

u16 Get_Number_From_Keypad(void)
{
	u8 key = NOT_PRESSED;
	u16 number = 0;

	while (1)
	{
		key = PressedKey();
		
		if (key != NOT_PRESSED)
		{
			if (key >= '0' && key <= '9')
			{
				lcd_send_data(key); // ?? ????? ????? ?? lcd_send_data ???????? ????
				number = (number * 10) + (key - '0');
			}
			else if (key == '=')
			{
				break;
			}
		}
	}
	return number;
}

#endif /* KEPAD_DRIVER_H_ */