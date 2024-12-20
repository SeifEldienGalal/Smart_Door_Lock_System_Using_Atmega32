#include "servo.h"
#include "../MCAL/gpio.h"
#include <avr/io.h>

void SERVO_init(void)
{
	// Set OC1A pin (PB1) as output
	GPIO_setupPinDirection(SERVO_PWM_PIN, PIN5_ID, PIN_OUTPUT);
	
	// Fast PWM, TOP = ICR1, Clear OC1A on compare match
	TCCR1A = (1 << WGM11) | (1 << COM1A1);
	TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11); // Prescaler 8
	
	// Set ICR1 for 20ms period (50Hz) - 16MHz / (8 * 50) = 40000
	ICR1 = 40000;
}

void SERVO_setAngle(uint8 angle)
{
	// Map angle (0-180) to pulse width (1000-2000 microseconds)
	// 1000us = 0 degrees, 2000us = 180 degrees
	uint16 pulse = 1000 + ((uint32)angle * 1000 / 180);
	
	// Convert pulse width to timer ticks
	OCR1A = (pulse * 2);
}