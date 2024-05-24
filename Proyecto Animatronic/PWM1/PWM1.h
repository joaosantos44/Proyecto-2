/*
 * PWM1.h
 *
 * Created: 18/05/2024 21:16:17
 *  Author: joaos
 */ 


#ifndef PWM1_H_
#define PWM1_H_

#include <avr/io.h>
#include <stdint.h>

#define Nor 0
#define Inv 1

#define bits_8 0
#define bits_9 1
#define bits_10 2
#define ICR1_set 3
#define OCR1_set 4

void setPWM1A(uint8_t INV_NOR, uint8_t ModoOnda, uint16_t Prescaler);
void DutyA1(uint8_t DutyCycle);

#endif /* PWM1_H_ */