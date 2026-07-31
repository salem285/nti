/*
 * TIMER_INTERRUPT.h
 *
 * Created: 2026-07-30 9:35:14 PM
 * Author: Mohamed
 */ 

#ifndef TIMER_INTERRUPT_H_
#define TIMER_INTERRUPT_H_

#include "STD_TYPES.h"
#include "GIO_DRIVER.h" // ?? ????? ???? ??? DIO ??? SET_BIT ? CLR_BIT

/* Global Interrupt & Timer Registers */
#define GICR  *( (volatile u8*) 0x5B )
#define SREG  *( (volatile u8*) 0x5F )
#define TCCR0 *( (volatile u8*) 0x53 )
#define TCNT0 *( (volatile u8*) 0x52 )
#define OCR0  *( (volatile u8*) 0x5C )
#define TIMSK *( (volatile u8*) 0x59 )

/* --- Timer & PWM Prototypes --- */
void Timer0_Init(u8 mode, u16 prescaler);
void Timer0_SetCompareMatchValue(u8 value);
void Timer0_EnableInterrupt(u8 int_type);
void Timer0_SetFastPWMMode(u8 pwm_mode);
void Timer0_SetDutyCycle(u8 duty_cycle, u8 pwm_mode);

/* --- Timer0 Driver Functions Implementation --- */

void Timer0_Init(u8 mode, u16 prescaler) {
	TCCR0 = 0x00;

	switch(mode) {
		case 0: CLR_BIT(TCCR0, 6); CLR_BIT(TCCR0, 3); break; // Normal
		case 1: SET_BIT(TCCR0, 6); CLR_BIT(TCCR0, 3); break; // Phase Correct PWM
		case 2: CLR_BIT(TCCR0, 6); SET_BIT(TCCR0, 3); break; // CTC
		case 3: SET_BIT(TCCR0, 6); SET_BIT(TCCR0, 3); break; // Fast PWM
	}

	switch(prescaler) {
		case 1:    TCCR0 |= 0b001; break;
		case 8:    TCCR0 |= 0b010; break;
		case 64:   TCCR0 |= 0b011; break;
		case 256:  TCCR0 |= 0b100; break;
		case 1024: TCCR0 |= 0b101; break;
	}
}

void Timer0_SetFastPWMMode(u8 pwm_mode) {
	if (pwm_mode == 2) {
		SET_BIT(TCCR0, 5); // Non-Inverting
		CLR_BIT(TCCR0, 4);
	}
	else if (pwm_mode == 3) {
		SET_BIT(TCCR0, 5); // Inverting
		SET_BIT(TCCR0, 4);
	}
}

void Timer0_SetDutyCycle(u8 duty_cycle, u8 pwm_mode) {
	if (duty_cycle > 100) duty_cycle = 100;

	if (pwm_mode == 2) {
		OCR0 = (u8)(((u16)duty_cycle * 255) / 100);
	}
	else if (pwm_mode == 3) {
		OCR0 = (u8)(255 - (((u16)duty_cycle * 255) / 100));
	}
}

void Timer0_SetCompareMatchValue(u8 value) {
	OCR0 = value;
}

void Timer0_EnableInterrupt(u8 int_type) {
	if (int_type == 0)      SET_BIT(TIMSK, 0); // OVF Interrupt
	else if (int_type == 1) SET_BIT(TIMSK, 1); // OC0 Interrupt
}

#endif /* TIMER_INTERRUPT_H_ */