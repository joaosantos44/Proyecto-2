/*
 * PWM0B.h
 *
 * Created: 7/05/2024 15:07:12
 *  Author: joaos
 */ 


#ifndef PWM0B_H_
#define PWM0B_H_

#include <avr/io.h>
#include <stdint.h>

#define Nor 0
#define Inv 1

#define PC_FF_0 0
#define Fast_FF_0 1
#define PC_OCRA_0 2
#define Modo_0 3
#define Fast_OCRA_0 4

void setPWM0B(uint8_t INV_NOR_B, uint8_t ModoOnda_B, uint16_t Prescaler_B);
void DutyB0(uint8_t DutyCycle_B);


#endif /* PWM0B_H_ */