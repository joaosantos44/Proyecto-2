/*
 * PWM1B.h
 *
 * Created: 18/05/2024 21:16:43
 *  Author: joaos
 */ 


#ifndef PWM1B_H_
#define PWM1B_H_

#include <avr/io.h>
#include <stdint.h>

#define Nor 0
#define Inv 1

#define bits_8 0
#define bits_9 1
#define bits_10 2
#define ICR1_set 3
#define OCR1_set 4

void setPWM1B(uint8_t INV_NOR_B, uint8_t ModoOnda_B, uint16_t Prescaler_B);
void DutyB1(uint8_t DutyCycle_B);

#endif /* PWM1B_H_ */