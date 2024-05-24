/*
 * PWM2.h
 *
 * Created: 18/05/2024 21:55:18
 *  Author: joaos
 */ 


#ifndef PWM2_H_
#define PWM2_H_

#include <avr/io.h>
#include <stdint.h>

#define Nor 0
#define Inv 1

#define PC_FF_0 0
#define Fast_FF_0 1
#define PC_OCRA_0 2
#define Modo_0 3
#define Fast_OCRA_0 4

void setPWM2A(uint8_t INV_NOR, uint8_t ModoOnda, uint16_t Prescaler);
void DutyA2(uint8_t DutyCycle);


#endif /* PWM2_H_ */