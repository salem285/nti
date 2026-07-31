/*
 * SEVEN_SEGMENT.h
 *
 * Created: 2026-07-30 7:39:04 PM
 * Author: Mohamed
 */ 

#ifndef SEVEN_SEGMENT_H_
#define SEVEN_SEGMENT_H_

#include "STD_TYPES.h"
#include "GIO_DRIVER.h" // ?? ????? ???? ??? DIO

/* 7-Segment Array for Numbers 0 to 9 */
const u8 SevenSeg_Numbers[10] = {
	0x3F, // 0
	0x06, // 1
	0x5B, // 2
	0x4F, // 3
	0x66, // 4
	0x6D, // 5
	0x7D, // 6
	0x07, // 7
	0x7F, // 8
	0x6F  // 9
};

/* Function Prototype */
void display_number(u8 num);

/* ==================== 7-Segment Function Implementation ==================== */

void display_number(u8 num) {
	u8 units = num % 10;
	DIO_SetPortValue(PORT_B, SevenSeg_Numbers[units]);
}

#endif /* SEVEN_SEGMENT_H_ */