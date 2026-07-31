/*
 * UART_DRIVER.h
 *
 * Created: 2026-07-30 9:21:52 PM
 * Author: Mohamed
 */ 

#ifndef UART_DRIVER_H_
#define UART_DRIVER_H_

#include "STD_TYPES.h"
#include "GIO_DRIVER.h" // ?? ????? ???? ??? DIO ??? SET_BIT

/* USART Registers Definitions */
#define UBRRH  *( (volatile u8*) 0x40 )
#define UCSRC  *( (volatile u8*) 0x40 )
#define UDR    *( (volatile u8*) 0x3C )
#define UCSRA  *( (volatile u8*) 0x2B )
#define UCSRB  *( (volatile u8*) 0x2A )
#define UBRRL  *( (volatile u8*) 0x29 )
#define ACSR   *( (volatile u8*) 0x28 )

/* UART Function Prototypes */
void UART_Init(void);
void UART_SendByte(u8 data);
u8   UART_ReceiveByte(void);
void UART_SendString(const u8* str);

/* --- UART Functions Implementation --- */

void UART_Init(void) {
	UBRRL = 51; // Baud Rate 9600 @ 8MHz
	UCSRC = (1 << 7) | (1 << 2) | (1 << 1); // URSEL=1, 8-bit data, 1 stop bit
	SET_BIT(UCSRB, 3); // TX Enable
	SET_BIT(UCSRB, 4); // RX Enable
}

void UART_SendByte(u8 data) {
	while (!(UCSRA & (1 << 5))); // Wait for UDRE
	UDR = data;
}

u8 UART_ReceiveByte(void) {
	while (!(UCSRA & (1 << 7))); // Wait for RXC
	return UDR;
}

void UART_SendString(const u8* str) {
	u8 i = 0;
	while (str[i] != '\0') {
		UART_SendByte(str[i]);
		i++;
	}
}

#endif /* UART_DRIVER_H_ */