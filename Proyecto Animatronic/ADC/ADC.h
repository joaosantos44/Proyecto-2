/*
 * ADC.h
 *
 * Created: 30/04/2024 15:43:56
 *  Author: joaos
 */ 




#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>
#include <stdint.h>


#define VoltOFF 0
#define Volt5 1
#define Volt1_1 2

#define JustDe 0
#define JustIz 1

#define OFF 0
#define ON 1

void ConfiADCPin(uint8_t VoltRef, uint8_t Just);
void ConfiADC(uint8_t Abil, uint8_t AutoTrig, uint8_t Inter, uint8_t Prescaler);

#endif /* ADC_H_ */