/*
 * STEPPER_MOTOR_DRIVER.h
 * Author: Mohamed
 */ 

#ifndef STEPPER_MOTOR_DRIVER_H_
#define STEPPER_MOTOR_DRIVER_H_

#include "STD_TYPES.h"
#include "GIO_DRIVER.h"

#ifndef F_CPU
#define F_CPU 8000000UL
#endif
#include <util/delay.h>

#define CW   0  
#define CCW  1

/* --- Function Declarations --- */
void STEPPER_Init(void);
void STEPPER_MoveStep(u8 step_index);
void STEPPER_Rotate(u16 steps, u8 direction, u16 speed_delay_ms);
void STEPPER_Stop(void);

/* --- Function Implementations --- */
void STEPPER_Init(void) {
    DIO_SetPinDirection(PORT_C, 0, OUTPUT);
    DIO_SetPinDirection(PORT_C, 1, OUTPUT);
    DIO_SetPinDirection(PORT_C, 2, OUTPUT);
    DIO_SetPinDirection(PORT_C, 3, OUTPUT);
}

void STEPPER_MoveStep(u8 step_index) {
    const u8 stepper_sequence[4] = {0x01, 0x02, 0x04, 0x08};
    PORTC = (PORTC & 0xF0) | (stepper_sequence[step_index % 4] & 0x0F);
}
void STEPPER_Rotate(u16 steps, u8 direction, u16 speed_delay_ms) {
	static u8 current_step = 0;
	
	for (u16 i = 0; i < steps; i++) {
		if (direction == CW) {
			current_step = (current_step + 1) % 4;
			} else {
			current_step = (current_step == 0) ? 3 : current_step - 1;
		}
		
		STEPPER_MoveStep(current_step);
		
		// ????? ?? _delay_ms(speed_delay_ms) ?????? ??? Error
		for (u16 d = 0; d < speed_delay_ms; d++) {
			_delay_ms(1);
		}
	}
}


void STEPPER_Stop(void) {
    PORTC &= 0xF0;
}

#endif /* STEPPER_MOTOR_DRIVER_H_ */