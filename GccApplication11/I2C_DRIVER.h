/*
 * I2C_DRIVER.h
 *
 * Created: 2026-07-30 9:52:38 PM
 * Author: Mohamed
 */ 

#ifndef I2C_DRIVER_H_
#define I2C_DRIVER_H_

#include "STD_TYPES.h"
#include "GIO_DRIVER.h" // ?? ????? ???? ??? DIO ?????? SET_BIT ? CLR_BIT

/* TWI (I2C) Registers Definitions */
#define TWBR    *( (volatile u8*) 0x20 )
#define TWCR    *( (volatile u8*) 0x56 )
#define TWSR    *( (volatile u8*) 0x21 )
#define TWDR    *( (volatile u8*) 0x23 )
#define TWAR    *( (volatile u8*) 0x22 )

/* Function Prototypes */
void I2C_INIT(u32 SCL_CLOCK);
void I2C_START(void);
void I2C_STOP(void);
void I2C_WRITE(u8 DATA);
u8   I2C_READ_ACK(void);
u8   I2C_READ_NACK(void); // ?? ????? ??? ??????? ?? u8

/* EEPROM Helper Functions Protocols */
void EEPROM_WriteByte(u8 address, u8 data);
u8   EEPROM_ReadByte(u8 address);

/* --- Function Implementations --- */

void I2C_INIT(u32 SCL_CLOCK) {
	u32 F_CPU1 = 8000000UL;
	TWBR = (u8)(((F_CPU1 / SCL_CLOCK) - 16) / 2);
	TWSR = 0b00000000; // Prescaler = 1
}

void I2C_START(void) {
	SET_BIT(TWCR, 2); // TWEN
	SET_BIT(TWCR, 5); // TWSTA
	SET_BIT(TWCR, 7); // TWINT
	while (!(TWCR & (1 << 7)));
}

void I2C_STOP(void) {
	SET_BIT(TWCR, 2); // TWEN
	SET_BIT(TWCR, 4); // TWSTO
	SET_BIT(TWCR, 7); // TWINT
}

void I2C_WRITE(u8 DATA) {
	TWDR = DATA;
	SET_BIT(TWCR, 2); // TWEN
	SET_BIT(TWCR, 7); // TWINT
	while (!(TWCR & (1 << 7)));
}

u8 I2C_READ_ACK(void) {
	SET_BIT(TWCR, 2); // TWEN
	SET_BIT(TWCR, 6); // TWEA
	SET_BIT(TWCR, 7); // TWINT
	while (!(TWCR & (1 << 7)));
	return TWDR;
}

u8 I2C_READ_NACK(void) {
	SET_BIT(TWCR, 2); // TWEN
	CLR_BIT(TWCR, 6); // TWEA = 0
	SET_BIT(TWCR, 7); // TWINT
	while (!(TWCR & (1 << 7)));
	return TWDR;
}

/* --- EEPROM I2C Functions --- */
void EEPROM_WriteByte(u8 address, u8 data) {
	I2C_START();
	I2C_WRITE(0xA0);   // EEPROM Address + Write
	I2C_WRITE(address);
	I2C_WRITE(data);
	I2C_STOP();
	_delay_ms(10);
}

u8 EEPROM_ReadByte(u8 address) {
	u8 data = 0;
	I2C_START();
	I2C_WRITE(0xA0);
	I2C_WRITE(address);
	
	I2C_START();       // Repeated Start
	I2C_WRITE(0xA1);   // EEPROM Address + Read
	data = I2C_READ_NACK();
	I2C_STOP();
	return data;
}

#endif /* I2C_DRIVER_H_ */