/*
 * GccApplication11.c
 * Integrated Syringe Pump Project
 * Author : Mohamed
 */ 

#define F_CPU 8000000UL     
#include <util/delay.h>    
#include <avr/interrupt.h>    

/* Include Application Drivers */
#include "STD_TYPES.h"
#include "GIO_DRIVER.h"     
#include "ADC_DRIVER.h"
#include "I2C_DRIVER.h"
#include "LCD_DRIVER.h"
#include "KEPAD_DRIVER.h"   
#include "SEVEN_SEGMENT.h"
#include "STEPPER_MOTOR_DRIVER.h"
#include "TIMER_INTERRUPT.h"
#include "UART_DRIVER.h"

#define OCCLUSION_LIMIT    700  // ?? ????? ?????
#define TEMP_LIMIT         40   // ?? ????? ??????? (LM35)

/* Pin Configuration Definitions */
#define LED_GREEN_PIN      0    // PORTA Pin 0 (?? ????)
#define LED_YELLOW_PIN     1    // PORTA Pin 1 (?????)
#define LED_RED_PIN        2    // PORTA Pin 2 (?????)

#define LIMIT_SWITCH_PIN   0    // PORTB Pin 0 (????? ?????)
#define EMERGENCY_BTN_PIN  1    // PORTB Pin 1 (?? ?????)
#define BOLUS_BTN_PIN      2    // PORTB Pin 2 (???? ?????)

int main(void)
{
	u16 volume = 0;
	u16 rate = 0;
	u16 pressure = 0;
	u16 temp_adc = 0;
	u8 temp_celsius = 0;
	u8 key = NOT_PRESSED;
	u8 step_index = 0;

	/* 1. Hardware Initialization Phase */
	ADC_Init();
	I2C_INIT(100000);     
	KEYPAD_Init();
	lcd_init();
	Timer0_Init(0, 64); // Normal Mode, Prescaler 64
	UART_Init();
	STEPPER_Init();

	/* ????? ????? ??? LEDs ?? Output */
	DIO_SetPinDirection(PORT_A, LED_GREEN_PIN, OUTPUT);
	DIO_SetPinDirection(PORT_A, LED_YELLOW_PIN, OUTPUT);
	DIO_SetPinDirection(PORT_A, LED_RED_PIN, OUTPUT);

	/* ????? ????? ???????? ?? Input Pull-up */
	DIO_SetPinDirection(PORT_B, LIMIT_SWITCH_PIN, INPUT);
	DIO_SetPinValue(PORT_B, LIMIT_SWITCH_PIN, HIGH);
	
	DIO_SetPinDirection(PORT_B, EMERGENCY_BTN_PIN, INPUT);
	DIO_SetPinValue(PORT_B, EMERGENCY_BTN_PIN, HIGH);

	DIO_SetPinDirection(PORT_B, BOLUS_BTN_PIN, INPUT);
	DIO_SetPinValue(PORT_B, BOLUS_BTN_PIN, HIGH);

	/* 2. Welcome Screen */
	lcd_send_command(0x01); _delay_ms(2);
	lcd_goto_xy(1, 0);
	lcd_send_string((u8*)"WELCOME IN:");
	lcd_goto_xy(2, 0);
	lcd_send_string((u8*)"SYRINGE PUMP");
	_delay_ms(2000);

	/* 3. User Input Data Phase */
	lcd_send_command(0x01); _delay_ms(2);
	lcd_goto_xy(1, 0);
	lcd_send_string((u8*)"Enter Vol (ml):");
	lcd_goto_xy(2, 0);
	volume = Get_Number_From_Keypad();

	lcd_send_command(0x01); _delay_ms(2);
	lcd_goto_xy(1, 0);
	lcd_send_string((u8*)"Enter Rate(ml/h):");
	lcd_goto_xy(2, 0);
	rate = Get_Number_From_Keypad();

	lcd_send_command(0x01); _delay_ms(2);
	lcd_goto_xy(1, 0);
	lcd_send_string((u8*)"Press 1 to Start");

	while (1)
	{
		key = PressedKey();
		if (key == '1') break;
	}

	UART_SendString((u8*)"Pumping Started...\r\n");
	
	// ????? ????? ?????? (???? ????)
	DIO_SetPinValue(PORT_A, LED_GREEN_PIN, HIGH);

	lcd_send_command(0x01); _delay_ms(2);
	lcd_goto_xy(1, 0);
	lcd_send_string((u8*)"Pumping Active");

	/* 4. Main Runtime Control Loop */
	while (1)
	{
		/* ????? ???????? ??? ??? ADC */
		pressure = ADC_Read(0);                 // Channel 0: Pressure Sensor
		temp_adc = ADC_Read(1);                 // Channel 1: LM35 Temp Sensor
		temp_celsius = (u8)((temp_adc * 500UL) / 1024); // ????? ??????? ???????

		/* ????? ???? ???????? */
		u8 limit_sw = DIO_GetPinValue(PORT_B, LIMIT_SWITCH_PIN);
		u8 emergency_btn = DIO_GetPinValue(PORT_B, EMERGENCY_BTN_PIN);
		u8 bolus_btn = DIO_GetPinValue(PORT_B, BOLUS_BTN_PIN);

		/* ??? ????? ??????? ???????? */
		if (pressure > OCCLUSION_LIMIT || temp_celsius > TEMP_LIMIT || limit_sw == LOW || emergency_btn == LOW)
		{
			STEPPER_Stop();                             // ????? ?????? ?????
			DIO_SetPinValue(PORT_A, LED_GREEN_PIN, LOW); // ????? ??????
			DIO_SetPinValue(PORT_A, LED_RED_PIN, HIGH);  // ????? ?????? (?????)
			
			// ????? ??????? ?? ????? ??? EEPROM ???????? ???????? I2C
			EEPROM_WriteByte(0x00, 0xEE); 

			UART_SendString((u8*)"ALARM: SYSTEM STOPPED!\r\n");

			lcd_send_command(0x01); _delay_ms(2);
			lcd_goto_xy(1, 0);
			lcd_send_string((u8*)"ERROR / STOPPED!");
			lcd_goto_xy(2, 0);
			
			if (pressure > OCCLUSION_LIMIT)       lcd_send_string((u8*)"Occlusion Error");
			else if (temp_celsius > TEMP_LIMIT)   lcd_send_string((u8*)"High Temp Alarm!");
			else if (limit_sw == LOW)             lcd_send_string((u8*)"End Limit Reached");
			else                                  lcd_send_string((u8*)"Emergency Stop!");

			while (1)
			{
				// ????? ???? ???? ??? Reset
			}
		}
		else
		{
			/* ???? ?????? ??????? Bolus */
			if (bolus_btn == LOW)
			{
				STEPPER_MoveStep(step_index++);
				display_number(rate % 100);
				_delay_ms(10); // ???? ??????
			}
			else
			{
				/* ???? ??????? */
				STEPPER_MoveStep(step_index++);
				display_number(rate % 100);
				_delay_ms(50);
			}
		}
	}
}