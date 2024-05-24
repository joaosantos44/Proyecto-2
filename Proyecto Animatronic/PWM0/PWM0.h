/*
 * PWM0.h
 *
 * Created: 7/05/2024 11:08:13
 *  Author: joaos
 */ 


#ifndef PWM0_H_
#define PWM0_H_


#include <avr/io.h>
#include <stdint.h>

#define Nor 0
#define Inv 1

#define PC_FF_0 0
#define Fast_FF_0 1
#define PC_OCRA_0 2
#define Modo_0 3
#define Fast_OCRA_0 4

void setPWM0A(uint8_t INV_NOR, uint8_t ModoOnda, uint16_t Prescaler);
void DutyA0(uint8_t DutyCycle);

#endif /* PWM0_H_ */