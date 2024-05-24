/*
 * PWM2.c
 *
 * Created: 18/05/2024 21:55:06
 *  Author: joaos
 */ 

#include "PWM2.h"
#include <avr/io.h>
#include <stdint.h>

void setPWM2A(uint8_t INV_NOR, uint8_t ModoOnda, uint16_t Prescaler){
	DDRB |= (1 << DDB3);
	TCCR2A = 0;

	
	
	if (INV_NOR == 1){
		TCCR2A |= (1 << COM2A1) | (1 << COM2A0);
	}
	else {
		TCCR2A |= (1 << COM2A1);
	}
	

	
	if (ModoOnda == 0){
		TCCR2A |= (1 << WGM20);
		TCCR2A &= ~(1 << WGM21);
	}
	else if (ModoOnda == 1){
		TCCR2A |= (1 << WGM20) | (1 << WGM21);
	}
	else if (ModoOnda == 2){
		TCCR2A |= (1 << WGM20);
		TCCR2A &= ~(1 << WGM21);
		TCCR2B |= (1 << WGM22);
	}
	else if (ModoOnda == 3){
		TCCR2A &= ~(1 << WGM20);
		TCCR2A &= ~(1 << WGM21);
	}
	else{
		TCCR2A |= (1 << WGM20) | (1 << WGM21);
		TCCR2B |= (1 << WGM22);
	}
	
	
	switch (Prescaler){
		case 0:
		TCCR2B |= (1 << CS20);
		break;
		case 8:
		TCCR2B |= (1 << CS21);
		break;
		case 64:
		TCCR2B |= (1 << CS20) | (1 << CS21);
		break;
		case 256:
		TCCR2B |= (1 << CS22);
		break;
		case 1024:
		TCCR2B |= (1 << CS20) | (1 << CS22);
		break;
		
		default:
		TCCR2B |= (1 << CS20);
	}
	
}


void DutyA2(uint8_t DutyCycle){
	OCR2A = DutyCycle;
}