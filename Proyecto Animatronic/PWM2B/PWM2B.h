/*
 * PWM2B.h
 *
 * Created: 18/05/2024 21:55:45
 *  Author: joaos
 */ 


#ifndef PWM2B_H_
#define PWM2B_H_

#include <avr/io.h>
#include <stdint.h>

#define Nor 0
#define Inv 1

#define PC_FF_0 0
#define Fast_FF_0 1
#define PC_OCRA_0 2
#define Modo_0 3
#define Fast_OCRA_0 4

void setPWM2B(uint8_t INV_NOR_B, uint8_t ModoOnda_B, uint16_t Prescaler_B);
void DutyB2(uint8_t DutyCycle_B);

#endif /* PWM2B_H_ */