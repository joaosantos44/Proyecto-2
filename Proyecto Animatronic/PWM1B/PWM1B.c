/*
 * PWM1B.c
 *
 * Created: 18/05/2024 21:16:55
 *  Author: joaos
 */ 

#include "PWM1B.h"
#include <avr/io.h>
#include <stdint.h>

void setPWM1B(uint8_t INV_NOR_B, uint8_t ModoOnda_B, uint16_t Prescaler_B){
	DDRB |= (1 << DDB2);
	
	if (INV_NOR_B == 1){
		TCCR1A |= (1 << COM1B1) | (1 << COM1B0);
	}
	else {
		TCCR1A |= (1 << COM1B1);
	}
	
	switch (ModoOnda_B){
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
	
	switch (Prescaler_B){
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


void DutyB1(uint8_t DutyCycle_B){
	OCR1B = DutyCycle_B;
}
