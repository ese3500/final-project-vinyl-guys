/*
 * RecordPlayerV1.c
 *
 * Created: 4/18/2024 4:14:47 PM
 * Author : Noah Rubin
 
 Photoresistor ADC to sense prescence of a record
 When theres a record slide ServoQ to ON position
 Push needle over ServoN
 Slide ServoQ back to OFF position
 
 */ 

#define F_CPU 16000000UL
#define BAUD_RATE 9600
#define BAUD_PRESCALER (((F_CPU / (BAUD_RATE * 16UL))) - 1)

#include "uart.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#include <util/delay.h>

char String[25];
int playing = 0;
int paused = 0;

void InitializeADC() {

	// Setup for ADC (10bit = 0-1023)
	// Clear power reduction bit for ADC
	PRR0 &= ~(1 << PRADC);

	// Select Vref = AVcc
	ADMUX |= (1 << REFS0);
	ADMUX &= ~(1 << REFS1);

	// Set the ADC clock div by 128
	// 16M/128=125kHz
	ADCSRA |= (1 << ADPS0);
	ADCSRA |= (1 << ADPS1);
	ADCSRA |= (1 << ADPS2);

	// Select Channel ADC0 (pin C0)
	ADMUX &= ~(1 << MUX0);
	ADMUX &= ~(1 << MUX1);
	ADMUX &= ~(1 << MUX2);
	ADMUX &= ~(1 << MUX3);

	ADCSRA |= (1 << ADATE);   // Autotriggering of ADC

	// Free running mode ADTS[2:0] = 000
	ADCSRB &= ~(1 << ADTS0);
	ADCSRB &= ~(1 << ADTS1);
	ADCSRB &= ~(1 << ADTS2);

	// Disable digital input buffer on ADC pin
	DIDR0 |= (1 << ADC0D);

	// Enable ADC
	ADCSRA |= (1 << ADEN);

	// Start conversion
	ADCSRA |= (1 << ADSC);
}

void InitializeRemoteInputs() {
	DDRC &= ~(1 << DDRC5); //blynk PLAY
	DDRC &= ~(1 << DDRC4); //blynk PAUSE
}

void InitializeServos(){
	DDRD |= (1 << DDD5); //Set pin PD6 as output for OC0B
	// Timer 0 setup pwm
	TCCR0A = 0x21; // Set OCR2B Table 18-8 in Datasheet. & Table 18-9.
	TCCR0B = 8; // Set WMG0[2]; tABLE 18-9
	TCNT0 = 0; // clear counter
	OCR0A = 156; // 20 ms period = 20000 us.
	OCR0B = 4; //
	TCCR0B |= 5; //set clock to divide by 1024 and start tALBE 18-10
	
	////////////////////////////////////////////
	/* old only one working
	DDRB |= (1 << DDB1);

	// Set Timer1 for Fast PWM mode 14 (ICR1 is top)
	TCCR1A |= (1 << WGM11);
	TCCR1B |= (1 << WGM12) | (1 << WGM13);

	// Set non-inverting mode for OC1A on PB1
	TCCR1A |= (1 << COM1A1);

	// Set ICR1 for a period of 20 ms with a prescaler of 8
	ICR1 = 39999; // 16MHz Clock / 8 prescaler / 50 Hz

	// Set prescaler to 8 and start the timer
	TCCR1B |= (1 << CS11);
	
	OCR1A = 2000;
	*/
	// Set PB1 and PB2 as output for OCR1A and OCR1B
	DDRB |= (1 << DDB1) | (1 << DDB2);

	// Configure Timer 1 for Fast PWM mode 14 (ICR1 is top)
	TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM11);  // Non-inverting mode
	TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11);     // Fast PWM, ICR1 as top, prescaler to 8

	// Set the ICR1 top value for a 50 Hz PWM frequency
	ICR1 = 39999;  // Calculation: (16 MHz / (8 prescaler * 50 Hz)) - 1

	// Set OCR1A and OCR1B for different servo positions
	OCR1A = 3000;  // Approximately 1.5 ms pulse width
	OCR1B = 3000;  // Set this differently if needed, for the second servo
	
	//////////////////////////////////////////////////////////////////////////
	
	// Set PE3 as an output pin for OC3A
	DDRD |= (1 << DDD2);  // Configure Pd0 as output

	// Clear Timer 3 Control Registers
	TCCR3A = 0;
	TCCR3B = 0;

	// Set Timer 3 to Fast PWM mode 14 (ICR3 is the top)
	TCCR3A |= (1 << WGM31) | (1 << COM3B1);  // Non-inverting PWM on OC3A
	TCCR3B |= (1 << WGM33) | (1 << WGM32);   // Use ICR3 as the top value

	// Set the ICR3 top value for a 50 Hz PWM frequency
	ICR3 = 39999; // Calculation: (16 MHz / (8 prescaler * 50 Hz)) - 1

	// Set the prescaler to 8 and start the timer
	TCCR3B |= (1 << CS31);  // Prescaler of 8

	// Set the OCR3A value for a neutral servo position (approximately 1.5 ms pulse width)
	OCR3B = 3000; // Approximately 1.5ms pulse width at 20ms period
}

// inputs degree values between 0 and 180
//inputs speed between 1 and 100
void moveServoA(int a, int b, int s) {
	double a0 = 4100.00 * a / 180.0;
	a0 += 900;
	a = a0;
	
	double b0 = 4100.00 * b / 180.0;
	b0 += 900;
	b = b0;
	
	s /= 4;
	
	if (a > b) {
		for (uint16_t i = a; i > b; i -= s) { // Pulse width from 1ms to 2ms
			OCR1A = i;
			_delay_ms(20);
		}
	}
	else{
		for (uint16_t i = a; i < b; i += s) { // Pulse width from 1ms to 2ms
			OCR1A = i;
			_delay_ms(20);
		}
	}
}

//inputs degree values between 0 and 90
void moveServoQ(int a, int b) {
	
	double a0 = 30.00 * a / 90.0;
	a = a0;
	
	double b0 = 30.00 * b / 90.0;
	b = b0;
		
	if (a > b) {
		for (uint16_t i = a; i > b; i -= 1) { // Pulse width from 1ms to 2ms
			OCR0B= i;
			_delay_ms(20);
		}
	}
	else {
		for (uint16_t i = a; i <= b; i += 1) { // Pulse width from 1ms to 2ms
			OCR0B= i;
			_delay_ms(20);
		}
	}
}

void pause() {
	moveServoQ(18, 0); // move the Q servo over
	_delay_ms(1000);
	OCR1B = 2000;
	_delay_ms(1000);
	OCR1B = 3500;
	_delay_ms(1000);
}

void play() {
	sprintf(String, "Move Servo Q (0, 75)\n");
	UART_putstring(String);
	
	moveServoQ(18, 0); // move the Q servo over 
	_delay_ms(1000);
	
	sprintf(String, "Move Servo A (0, 180)\n");
	UART_putstring(String);
	 
	moveServoA(180, 0, 80); //move the arm servo
	_delay_ms(1000);
	
	sprintf(String, "Move Servo A (180, 0)\n");
	UART_putstring(String);
	
	moveServoA(0, 180, 80); //move the arm servo back
	_delay_ms(1000);
	
	sprintf(String, "Move Servo Q (75, 0)\n");
	UART_putstring(String);
	moveServoQ(0, 18); //move the q servo back to lower the needle and start playing
} 

void init() {
	
	UART_init(BAUD_PRESCALER);
	
	sprintf(String, "Starting Program");
	UART_putstring(String);
	
	InitializeServos();
	InitializeADC();
	InitializeRemoteInputs();
	
}

int main(void)
{
	init();
	
	while (1) {	
		
		//sprintf(String, "ADC %d \n", ADC);
		//UART_putstring(String);
		
		if (((ADC > 1015) && (paused == 0)) || (PINC & 0x10)) {
			if (playing == 0) {
				playing = 1;
				paused = 0;
				sprintf(String, "PLAY", ADC);
				UART_putstring(String);
				_delay_ms(1000);
				play();
			}
		}
		else if ((PINC & 0x20) && (playing > 0)) { 
			playing = 0;
			paused = 1;
			sprintf(String, "PAUSE", ADC);
			UART_putstring(String);
			pause();
		}
		
		if ((ADC < 1010) && (paused == 1)) {
			paused = 0;
		}
		
		
	}
}
