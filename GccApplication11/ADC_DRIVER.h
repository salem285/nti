/*
 * ADC_DRIVER.h
 *
 * Created: 2026-07-30 9:44:05 PM
 * Author: Mohamed
 */ 

#ifndef ADC_DRIVER_H_
#define ADC_DRIVER_H_

#include "STD_TYPES.h"
#include "GIO_DRIVER.h" // ?????? ?????? SET_BIT ? CLR_BIT

/* ADC Registers Definitions */
#define ADMUX     *( (volatile u8*)  0x27 )
#define ADCSRA    *( (volatile u8*)  0x26 )
#define ADCH      *( (volatile u8*)  0x25 )
#define ADCL      *( (volatile u8*)  0x24 )
#define ADC_DATA  *( (volatile u16*) 0x24 )

/* ADC Functions Prototypes */
void ADC_Init(void);
u16  ADC_Read(u8 channel);

/* --- ADC Driver Functions Implementation --- */

void ADC_Init(void) {
	SET_BIT(ADMUX, 6);  // AVCC Reference
	CLR_BIT(ADMUX, 7);

	/* Prescaler 64 & Enable ADC */
	SET_BIT(ADCSRA, 7); // ADEN (ADC Enable)
	SET_BIT(ADCSRA, 2);
	SET_BIT(ADCSRA, 1);
	CLR_BIT(ADCSRA, 0);
}

u16 ADC_Read(u8 channel) {
	ADMUX = (ADMUX & 0xE0) | (channel & 0x07);
	SET_BIT(ADCSRA, 6); // Start conversion (ADSC)
	while (ADCSRA & (1 << 6)); // Wait for completion
	return ADC_DATA;
}

#endif /* ADC_DRIVER_H_ */