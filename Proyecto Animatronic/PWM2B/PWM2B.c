/*
 * PWM2B.c
 *
 * Created: 18/05/2024 21:55:34
 *  Author: joaos
 */ 

#include "PWM2B.h"
#include <avr/io.h>
#include <stdint.h>

void setPWM2B(uint8_t INV_NOR_B, uint8_t ModoOnda_B, uint16_t Prescaler_B){
	DDRD |= (1 << DDD3);

	TCCR2B = 0;
	
	
	if (INV_NOR_B == 1){
		TCCR2A |= (1 << COM2B1) | (1 << COM2B0);
	}
	else {
		TCCR2A |= (1 << COM2B1);
	}
	

	
	if (ModoOnda_B == 0){
		TCCR2A |= (1 << WGM20);
		TCCR2A &= ~(1 << WGM21);
	}
	else if (ModoOnda_B == 1){
		TCCR2A |= (1 << WGM20) | (1 << WGM21);
	}
	else if (ModoOnda_B == 2){
		TCCR2A |= (1 << WGM20);
		TCCR2A &= ~(1 << WGM21);
		TCCR2B |= (1 << WGM22);
	}
	else if (ModoOnda_B == 3){
		TCCR2A &= ~(1 << WGM20);
		TCCR2A &= ~(1 << WGM21);
	}
	else{
		TCCR2A |= (1 << WGM20) | (1 << WGM21);
		TCCR2B |= (1 << WGM22);
	}
	
	
	switch (Prescaler_B){
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


void DutyB2(uint8_t DutyCycle_B){
	OCR2B = DutyCycle_B;
}