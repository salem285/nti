/*
 * GIO_DRIVER.h
 *
 * Created: 2026-07-30 6:59:18 PM
 * Author: Mohamed
 */ 
#ifndef GIO_DRIVER_H_
#define GIO_DRIVER_H_

/* Include Standard Types */
#include "STD_TYPES.h"

/* Bit Math Macros */
#define SET_BIT(REG, BIT_NO)    (REG |= (1 << BIT_NO))
#define CLR_BIT(REG, BIT_NO)    (REG &= ~(1 << BIT_NO))
#define TOG_BIT(REG, BIT_NO)    (REG ^= (1 << BIT_NO))

/* GPIO Registers */
#define DDRA  *( (volatile u8*) 0x3A )
#define PORTA *( (volatile u8*) 0x3B )
#define PINA  *( (volatile u8*) 0x39 )

#define DDRB  *( (volatile u8*) 0x37 )
#define PORTB *( (volatile u8*) 0x38 )
#define PINB  *( (volatile u8*) 0x36 )

#define DDRC  *( (volatile u8*) 0x34 )
#define PORTC *( (volatile u8*) 0x35 )
#define PINC  *( (volatile u8*) 0x33 )

#define DDRD  *( (volatile u8*) 0x31 )
#define PORTD *( (volatile u8*) 0x32 )
#define PIND  *( (volatile u8*) 0x30 )

#define PORT_A   1
#define PORT_B   2
#define PORT_C   3
#define PORT_D   4

#define INPUT    0x00
#define OUTPUT   0xFF

#define HIGH     1
#define LOW      0

/* Pin Level Prototypes */
void DIO_SetPinDirection(u8 u8PortIdCopy, u8 u8PinIdCopy, u8 u8PinDirCopy);
void DIO_SetPinValue(u8 u8PortIdCopy, u8 u8PinIdCopy, u8 u8PinValCopy);
u8   DIO_GetPinValue(u8 u8PortIdCopy, u8 u8PinIdCopy);
void DIO_TogglePinValue(u8 u8PortIdCopy, u8 u8PinIdCopy);

/* Port Level Prototypes */
void DIO_SetPortDirection(u8 u8PortIdCopy, u8 u8PortDirCopy);
void DIO_SetPortValue(u8 u8PortIdCopy, u8 u8PortValCopy);
void DIO_TogglePortValue(u8 u8PortIdCopy);
u8   DIO_GetPortValue(u8 u8PortIdCopy);

/* DIO Pin-Level Functions Implementation  */

void DIO_SetPinDirection(u8 u8PortIdCopy, u8 u8PinIdCopy, u8 u8PinDirCopy) {
	if (u8PinDirCopy == HIGH || u8PinDirCopy == OUTPUT) {
		switch (u8PortIdCopy) {
			case PORT_A: SET_BIT(DDRA, u8PinIdCopy); break;
			case PORT_B: SET_BIT(DDRB, u8PinIdCopy); break;
			case PORT_C: SET_BIT(DDRC, u8PinIdCopy); break;
			case PORT_D: SET_BIT(DDRD, u8PinIdCopy); break;
		}
	}
	else if (u8PinDirCopy == LOW || u8PinDirCopy == INPUT) {
		switch (u8PortIdCopy) {
			case PORT_A: CLR_BIT(DDRA, u8PinIdCopy); break;
			case PORT_B: CLR_BIT(DDRB, u8PinIdCopy); break;
			case PORT_C: CLR_BIT(DDRC, u8PinIdCopy); break;
			case PORT_D: CLR_BIT(DDRD, u8PinIdCopy); break;
		}
	}
}

void DIO_SetPinValue(u8 u8PortIdCopy, u8 u8PinIdCopy, u8 u8PinValCopy) {
	if (u8PinValCopy == HIGH) {
		switch (u8PortIdCopy) {
			case PORT_A: SET_BIT(PORTA, u8PinIdCopy); break;
			case PORT_B: SET_BIT(PORTB, u8PinIdCopy); break;
			case PORT_C: SET_BIT(PORTC, u8PinIdCopy); break;
			case PORT_D: SET_BIT(PORTD, u8PinIdCopy); break;
		}
	}
	else if (u8PinValCopy == LOW) {
		switch (u8PortIdCopy) {
			case PORT_A: CLR_BIT(PORTA, u8PinIdCopy); break;
			case PORT_B: CLR_BIT(PORTB, u8PinIdCopy); break;
			case PORT_C: CLR_BIT(PORTC, u8PinIdCopy); break;
			case PORT_D: CLR_BIT(PORTD, u8PinIdCopy); break;
		}
	}
}

u8 DIO_GetPinValue(u8 u8PortIdCopy, u8 u8PinIdCopy) {
	u8 u8Result = 0;
	switch (u8PortIdCopy) {
		case PORT_A: u8Result = ((PINA >> u8PinIdCopy) & 0x01); break;
		case PORT_B: u8Result = ((PINB >> u8PinIdCopy) & 0x01); break;
		case PORT_C: u8Result = ((PINC >> u8PinIdCopy) & 0x01); break;
		case PORT_D: u8Result = ((PIND >> u8PinIdCopy) & 0x01); break;
	}
	return u8Result;
}

void DIO_TogglePinValue(u8 u8PortIdCopy, u8 u8PinIdCopy) {
	switch (u8PortIdCopy) {
		case PORT_A: TOG_BIT(PORTA, u8PinIdCopy); break;
		case PORT_B: TOG_BIT(PORTB, u8PinIdCopy); break;
		case PORT_C: TOG_BIT(PORTC, u8PinIdCopy); break;
		case PORT_D: TOG_BIT(PORTD, u8PinIdCopy); break;
	}
}

/* --- DIO Port-Level Functions Implementation --- */

void DIO_SetPortDirection(u8 u8PortIdCopy, u8 u8PortDirCopy) {
	switch (u8PortIdCopy) {
		case PORT_A: DDRA = u8PortDirCopy; break;
		case PORT_B: DDRB = u8PortDirCopy; break;
		case PORT_C: DDRC = u8PortDirCopy; break;
		case PORT_D: DDRD = u8PortDirCopy; break;
	}
}

void DIO_SetPortValue(u8 u8PortIdCopy, u8 u8PortValCopy) {
	switch (u8PortIdCopy) {
		case PORT_A: PORTA = u8PortValCopy; break;
		case PORT_B: PORTB = u8PortValCopy; break;
		case PORT_C: PORTC = u8PortValCopy; break;
		case PORT_D: PORTD = u8PortValCopy; break;
	}
}

void DIO_TogglePortValue(u8 u8PortIdCopy) {
	switch (u8PortIdCopy) {
		case PORT_A: PORTA = ~PORTA; break;
		case PORT_B: PORTB = ~PORTB; break;
		case PORT_C: PORTC = ~PORTC; break;
		case PORT_D: PORTD = ~PORTD; break;
	}
}

u8 DIO_GetPortValue(u8 u8PortIdCopy) {
	u8 u8Result = 0;
	switch (u8PortIdCopy) {
		case PORT_A: u8Result = PINA; break;
		case PORT_B: u8Result = PINB; break;
		case PORT_C: u8Result = PINC; break;
		case PORT_D: u8Result = PIND; break;
	}
	return u8Result;
}

#endif /* GIO_DRIVER_H_ */