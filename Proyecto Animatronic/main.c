/******************************************************************************
;Universidad del Valle de Guatemala
;IE2023: Programacion de Microcontroladores
;Antirebote.asm
;Autor; Joao Santos
;Proyecto Servos
;Hardware: Atemega328P
;Creado: 15/04/2024
;Ultima modificacion: 22/04/2024
******************************************************************************/
#define F_CPU 16000000
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include "ADC/ADC.h"
#include "PWM0/PWM0.h"
#include "PWM0B/PWM0B.h"
#include "PWM1/PWM1.h"
#include "PWM1B/PWM1B.h"
//#include "PWM2/PWM2.h"
//#include "PWM2B/PWM2B.h"

uint8_t Pociciones_EPROM = 0;
uint8_t Modos = 0;
uint16_t dutyCycle1;
uint16_t dutyCycle2;
uint16_t dutyCycle3;
uint16_t dutyCycle4;
uint16_t* Uno_address = 0x20;
uint16_t* Dos_address = 0x40;
uint16_t* Tres_address = 0x60;
uint16_t* Cuatro_address = 0x0F;
volatile uint8_t buffer_ADC;
volatile char bufferRX;
volatile uint8_t buffer_RX_B;

void PINCHANGE(void);
void Servo_en_vivo(void);
void SetUp(void);

void InitUART9600(void);
void witetextUART(char* texto);

void Uno_write (void);
void Uno_read (void);
void Dos_write (void);
void Dos_read (void);
void Tres_write (void);
void Tres_read (void);
void Cuatro_write (void);
void Cuatro_read (void);

uint16_t valorADC (uint8_t canal) {
	ADMUX &= 0xF0;
	ADMUX |= canal;
	
	ADCSRA |= (1 << ADSC);
	
	while (ADCSRA & (1 << ADSC));
	
	return ADCH;
}

int main(void){

	uint16_t dutyCycle1 = valorADC(7);
	uint16_t dutyCycle2 = valorADC(6);
	uint16_t dutyCycle3 = valorADC(5);
	uint16_t dutyCycle4 = valorADC(4);
	
	PINCHANGE();
	SetUp();
	InitUART9600();
	
	/*
	Uno_write ();
	Uno_read ();
	Dos_write ();
	Dos_read ();
	Tres_write ();
	Tres_read ();
	Cuatro_write ();
	Cuatro_read ();
	*/
	
	setPWM0A(Nor, Fast_FF_0, 1024);
	setPWM0B(Nor, Fast_FF_0, 1024);
	setPWM1A(Nor, bits_8, 1024);
	setPWM1B(Nor, bits_8, 1024);
	//setPWM2A(Nor, Fast_FF_0, 1024);
	//setPWM2B(Nor, Fast_FF_0, 1024);
	
	ConfiADCPin(Volt5, JustIz);
	ConfiADC(ON, OFF, OFF, 128);
	
	
	sei();
	
	witetextUART("Elija su pocicion (No es con el pad numerico =D) \nPocicion Uno (1) \nPocicion Dos (2) \nPocicion Tres (3) \nPocicion Cuatro (4)");
	
	while (1){
		
		if (Modos == 1){
			//PORTD &= ~(1 << DDD7);
			//PORTD &= ~(1 << DDD4);
			//PORTD |= (1 << DDD7);
			//PORTD &= ~(1 << DDD4);
			
			
			if (Pociciones_EPROM == 1){
				Uno_write();
				PORTD &= ~(1 << DDD7);
				PORTD &= ~(1 << DDD4);
			}else if (Pociciones_EPROM == 2){
				Dos_write();
				PORTD |= (1 << DDD4);
				PORTD &= ~(1 << DDD7);
			}else if (Pociciones_EPROM == 3){
				Tres_write();
				PORTD |= (1 << DDD7);
				PORTD &= ~(1 << DDD4);
			}else if (Pociciones_EPROM = 4){
				Cuatro_write();
				PORTD |= (1 << DDD7);
				PORTD |= (1 << DDD4);
			}
			
			
		}else if (Modos == 2){
			PORTD |= (1 << DDD4);
			PORTD &= ~(1 << DDD7);
			
			
			if (Pociciones_EPROM == 1){
				Uno_read();
			}else if (Pociciones_EPROM == 2){
				Dos_read();
			}else if (Pociciones_EPROM == 3){
				Tres_read();
			}else if (Pociciones_EPROM = 4){
				Cuatro_read();
			}
			
			
		}else if (Modos == 3){
			PORTD |= (1 << DDD7);
			PORTD |= (1 << DDD4);
			
			if (UDR0 == 49) {
				Uno_read();
			} else if (UDR0 == 50) {
				Dos_read();
			} else if (UDR0 == 51) {
				Tres_read();
			} else if (UDR0 == 52) {
				Cuatro_read();
			}
			
			
		}else if (Modos == 4){
			Modos = 0;
			PORTD &= ~(1 << DDD7);
			PORTD &= ~(1 << DDD4);
		} 
	}
	return 0;
}

void SetUp(void){
	
	DDRD |= (1 << PIND7) | (1 << PIND4);
	PORTD &= ~(1 << PIND7);
	PORTD &= ~(1 << PIND4);
	
	DIDR0 |= (1 << ADC5D);
	DIDR0 |= (1 << ADC4D);
	
	DDRD &= ~((1 << PIND2));
	PORTD |= (1 << PIND2);
	
	DDRC &= ~((1 << PINC0) | (1 << PINC1) | (1 << PINC2) | (1 << PINC3));
	PORTC |= (1 << PINC0) | (1 << PINC1) | (1 << PINC2) | (1 << PINC3);
}

void Servo_en_vivo(void){
	dutyCycle1 = valorADC(7);
	_delay_ms(10);
	DutyA0(dutyCycle1/6);
	
	dutyCycle2 = valorADC(6);
	_delay_ms(10);
	DutyB0(dutyCycle2/6);
	
	dutyCycle3 = valorADC(5);
	_delay_ms(10);
	DutyA1(dutyCycle3/6);

	dutyCycle4 = valorADC(4);
	_delay_ms(10);
	DutyB1(dutyCycle4/6);
	
	_delay_ms(25);
}

void PINCHANGE(void){
	// Activar las interupciones de PC1 (Puerto C)
	PCICR |= (1 << PCIE1);
	// Activar las interupciones de PC2 (Puerto D)
	PCICR |= (1 << PCIE2);
	// Activar las interupciones de PC1 (Pines 0C, 1C, 2C y 3C)
	PCMSK1 |= (1 << PCINT8) | (1 << PCINT9) | (1 << PCINT10) | (1 << PCINT11);
	// Activar las interupciones de PC2 (Pin 2D)
	PCMSK2 |= (1 << PCINT18);
}

void Uno_write (void){
	
	Servo_en_vivo();
	
	dutyCycle1 = valorADC(7);
	dutyCycle2 = valorADC(6);
	dutyCycle3 = valorADC(5);
	dutyCycle4 = valorADC(4);
	
	uint16_t Primer_Gesto[4] = {dutyCycle1, dutyCycle2, dutyCycle3, dutyCycle4};
	
	eeprom_write_block((const void*)Primer_Gesto, (void*)Uno_address, sizeof(Primer_Gesto));
	
}


void Uno_read (void){
	
	uint16_t read_Uno_eeprom[4];
	
	eeprom_read_block((void*)read_Uno_eeprom, (const void*)Uno_address, sizeof(read_Uno_eeprom));
	
	dutyCycle1= read_Uno_eeprom[0];
	dutyCycle2= read_Uno_eeprom[1];
	dutyCycle3= read_Uno_eeprom[2];
	dutyCycle4= read_Uno_eeprom[3];
	
	DutyA0(dutyCycle1/6);
	_delay_ms(10);
	DutyB0(dutyCycle2/6);
	_delay_ms(10);
	DutyA1(dutyCycle3/6);
	_delay_ms(10);
	DutyB1(dutyCycle4/6);
	_delay_ms(10);
}

void Dos_write (void){
	
	Servo_en_vivo();
	
	dutyCycle1 = valorADC(7);
	dutyCycle2 = valorADC(6);
	dutyCycle3 = valorADC(5);
	dutyCycle4 = valorADC(4);
	
	uint16_t Segundo_Gesto[4] = {dutyCycle1, dutyCycle2, dutyCycle3, dutyCycle4};
	
	eeprom_write_block((const void*)Segundo_Gesto, (void*)Dos_address, sizeof(Segundo_Gesto));
	
}


void Dos_read (void){
	
	uint16_t read_Dos_eeprom[4];
	
	eeprom_read_block((void*)read_Dos_eeprom, (const void*)Dos_address, sizeof(read_Dos_eeprom));
	
	dutyCycle1= read_Dos_eeprom[0];
	dutyCycle2= read_Dos_eeprom[1];
	dutyCycle3= read_Dos_eeprom[2];
	dutyCycle4= read_Dos_eeprom[3];
	
	DutyA0(dutyCycle1/6);
	_delay_ms(10);
	DutyB0(dutyCycle2/6);
	_delay_ms(10);
	DutyA1(dutyCycle3/6);
	_delay_ms(10);
	DutyB1(dutyCycle4/6);
	_delay_ms(10);
}


void Tres_write (void){
	
	Servo_en_vivo();
	
	dutyCycle1 = valorADC(7);
	dutyCycle2 = valorADC(6);
	dutyCycle3 = valorADC(5);
	dutyCycle4 = valorADC(4);
	
	uint16_t Tercer_Gesto[4] = {dutyCycle1, dutyCycle2, dutyCycle3, dutyCycle4};
	
	eeprom_write_block((const void*)Tercer_Gesto, (void*)Tres_address, sizeof(Tercer_Gesto));
	
}


void Tres_read (void){
	
	uint16_t read_Tres_eeprom[4];
	
	eeprom_read_block((void*)read_Tres_eeprom, (const void*)Tres_address, sizeof(read_Tres_eeprom));
	
	dutyCycle1= read_Tres_eeprom[0];
	dutyCycle2= read_Tres_eeprom[1];
	dutyCycle3= read_Tres_eeprom[2];
	dutyCycle4= read_Tres_eeprom[3];
	
	DutyA0(dutyCycle1/6);
	_delay_ms(10);
	DutyB0(dutyCycle2/6);
	_delay_ms(10);
	DutyA1(dutyCycle3/6);
	_delay_ms(10);
	DutyB1(dutyCycle4/6);
	_delay_ms(10);
}


void Cuatro_write (void){
	
	Servo_en_vivo();
	
	dutyCycle1 = valorADC(7);
	dutyCycle2 = valorADC(6);
	dutyCycle3 = valorADC(5);
	dutyCycle4 = valorADC(4);
	
	uint16_t Cuarto_Gesto[4] = {dutyCycle1, dutyCycle2, dutyCycle3, dutyCycle4};
	
	eeprom_write_block((const void*)Cuarto_Gesto, (void*)Cuatro_address, sizeof(Cuarto_Gesto));
	
}


void Cuatro_read (void){
	
	uint16_t read_Cuatro_eeprom[4];
	
	eeprom_read_block((void*)read_Cuatro_eeprom, (const void*)Cuatro_address, sizeof(read_Cuatro_eeprom));
	
	dutyCycle1= read_Cuatro_eeprom[0];
	dutyCycle2= read_Cuatro_eeprom[1];
	dutyCycle3= read_Cuatro_eeprom[3];
	dutyCycle4= read_Cuatro_eeprom[4];
	
	DutyA0(dutyCycle1/6);
	_delay_ms(10);
	DutyB0(dutyCycle2/6);
	_delay_ms(10);
	DutyA1(dutyCycle3/6);
	_delay_ms(10);
	DutyB1(dutyCycle4/6);
	_delay_ms(10);
}

void InitUART9600(void){
	//Confi TX y RX
	DDRD &= ~(1 << DDD0);
	DDRD |= (1 << DDD1);
	
	//Confi Registro A Modo Fast U2X0 = 1
	UCSR0A = 0;
	UCSR0A |= (1 << U2X0);
	
	//Confi Registro B habilitar ISR de RX, habilitamos RX y TX
	UCSR0B = 0;
	UCSR0B |= (1 << RXCIE0) | (1 << RXEN0) | (1 << TXEN0);
	
	//Confi Registro C > Frame: 8 bits No pariedad ! bit stop
	UCSR0C = 0;
	UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);
	
	//Baudrate
	UBRR0 = 207;
}


void witetextUART(char* texto){
	uint8_t i;
	for (i = 0; texto[i] != '\0'; i++){
		while(!(UCSR0A & (1 << UDRE0)));
		UDR0 = texto[i];
	}
}

ISR(USART_RX_vect){
	
	bufferRX = UDR0;
	buffer_RX_B = UDR0;
	while(!(UCSR0A & (1 << UDRE0)));
	UDR0 = bufferRX;
	UDR0 = buffer_RX_B;
	
}



ISR(PCINT1_vect){
	// Set de botones
	uint8_t EP1 = PINC & (1 << PINC0);
	uint8_t EP2 = PINC & (1 << PINC1);
	uint8_t EP3 = PINC & (1 << PINC2);
	uint8_t EP4 = PINC & (1 << PINC3);
	// Incremento y decremento


	if (EP1 == 0){
		Pociciones_EPROM = 1;
	}else if (EP2 == 0){
		Pociciones_EPROM = 2;
	}else if (EP3 == 0){
		Pociciones_EPROM = 3;
	}else if (EP4 == 0){
		Pociciones_EPROM = 4;
	}

	// Desactivado de banderas
	PCIFR |= (1 << PCIF1);
}


ISR(PCINT2_vect){
	// Set de botones
	uint8_t Muds = PIND & (1 << PIND2);
	// Incremento y decremento

	if (Muds == 0){
		Modos++;
	}

	// Desactivado de banderas
	PCIFR |= (1 << PCIF2);
}