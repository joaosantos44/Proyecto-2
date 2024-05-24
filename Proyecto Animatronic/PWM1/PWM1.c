/*
 * PWM1.c
 *
 * Created: 18/05/2024 21:15:55
 *  Author: joaos
 */ 

#include "PWM1.h"
#include <avr/io.h>
#include <stdint.h>

void setPWM1A(uint8_t INV_NOR, uint8_t ModoOnda, uint16_t Prescaler){
	DDRB |= (1 << DDB1);
	
	TCCR1B = 0;
	
	if (INV_NOR == 1){
		TCCR1A |= (1 << COM1A1) | (1 << COM1A0);
	}
	else {
		TCCR1A |= (1 << COM1A1);
	}
	
	switch (ModoOnda){
		case 0:
		TCCR1A |= (1 << WGM10);
		TCCR1B |= (1 << WGM12);
		break;
		case 1:
		TCCR1A |= (1 << WGM11);
		TCCR1B |= (1 << WGM12);
		break;
		case 2:
		TCCR1A |= (1 << WGM10) | (1 << WGM11);
		TCCR1B |= (1 << WGM12);
		break;
		case 3:
		TCCR1A |= (1 << WGM10);
		TCCR1B |= (1 << WGM12) | (1 << WGM13);
		break;
		case 4:
		TCCR1A |= (1 << WGM10) | (1 << WGM11);
		TCCR1B |= (1 << WGM12) | (1 << WGM13);
		break;
		
		default:
		TCCR1A |= (1 << WGM10);
		TCCR1B |= (1 << WGM12);
	}
	
	switch (Prescaler){
		case 0:
		TCCR1B |= (1 << CS10);
		break;
		case 8:
		TCCR1B |= (1 << CS11);
		break;
		case 64:
		TCCR1B |= (1 << CS10) | (1 << CS11);
		break;
		case 256:
		TCCR1B |= (1 << CS12);
		break;
		case 1024:
		TCCR1B |= (1 << CS10) | (1 << CS12);
		break;
		
		default:
		TCCR1B |= (1 << CS10);
	}
	
}


void DutyA1(uint8_t DutyCycle){
	OCR1A = DutyCycle;
}
