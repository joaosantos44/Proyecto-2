/*
 * PWM0.c
 *
 * Created: 7/05/2024 11:07:23
 *  Author: joaos
 */ 


#include "PWM0.h"
#include <avr/io.h>
#include <stdint.h>

void setPWM0A(uint8_t INV_NOR, uint8_t ModoOnda, uint16_t Prescaler){
	DDRD |= (1 << DDD6);
	TCCR0A = 0;

	
	
	if (INV_NOR == 1){
		TCCR0A |= (1 << COM0A1) | (1 << COM0A0);
	}
	else {
		TCCR0A |= (1 << COM0A1);
	}
	

	
	if (ModoOnda == 0){
		TCCR0A |= (1 << WGM00);
		TCCR0A &= ~(1 << WGM01);
	}
	else if (ModoOnda == 1){
		TCCR0A |= (1 << WGM00) | (1 << WGM01);
	}
	else if (ModoOnda == 2){
		TCCR0A |= (1 << WGM00);
		TCCR0A &= ~(1 << WGM01);
		TCCR0B |= (1 << WGM02);
	}
	else if (ModoOnda == 3){
		TCCR0A &= ~(1 << WGM00);
		TCCR0A &= ~(1 << WGM01);
	}
	else{
		TCCR0A |= (1 << WGM00) | (1 << WGM01);
		TCCR0B |= (1 << WGM02);
	}
	
	
	switch (Prescaler){
		case 0:
		TCCR0B |= (1 << CS00);
		break;
		case 8:
		TCCR0B |= (1 << CS01);
		break;
		case 64:
		TCCR0B |= (1 << CS00) | (1 << CS01);
		break;
		case 256:
		TCCR0B |= (1 << CS02);
		break;
		case 1024:
		TCCR0B |= (1 << CS00) | (1 << CS02);
		break;
		
		default:
		TCCR0B |= (1 << CS00);
	}
	
}


void DutyA0(uint8_t DutyCycle){
	OCR0A = DutyCycle;
}