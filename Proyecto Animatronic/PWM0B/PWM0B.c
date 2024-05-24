/*
 * PWM0B.c
 *
 * Created: 7/05/2024 15:07:30
 *  Author: joaos
 */ 



#include "PWM0B.h"
#include <avr/io.h>
#include <stdint.h>

void setPWM0B(uint8_t INV_NOR_B, uint8_t ModoOnda_B, uint16_t Prescaler_B){
	DDRD |= (1 << DDD5);

	TCCR0B = 0;
	
	
	if (INV_NOR_B == 1){
		TCCR0A |= (1 << COM0B1) | (1 << COM0B0);
	}
	else {
		TCCR0A |= (1 << COM0B1);
	}
	

	
	if (ModoOnda_B == 0){
		TCCR0A |= (1 << WGM00);
		TCCR0A &= ~(1 << WGM01);
	}
	else if (ModoOnda_B == 1){
		TCCR0A |= (1 << WGM00) | (1 << WGM01);
	}
	else if (ModoOnda_B == 2){
		TCCR0A |= (1 << WGM00);
		TCCR0A &= ~(1 << WGM01);
		TCCR0B |= (1 << WGM02);
	}
	else if (ModoOnda_B == 3){
		TCCR0A &= ~(1 << WGM00);
		TCCR0A &= ~(1 << WGM01);
	}
	else{
		TCCR0A |= (1 << WGM00) | (1 << WGM01);
		TCCR0B |= (1 << WGM02);
	}
	
	
	switch (Prescaler_B){
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


void DutyB0(uint8_t DutyCycle_B){
	OCR0B = DutyCycle_B;
}