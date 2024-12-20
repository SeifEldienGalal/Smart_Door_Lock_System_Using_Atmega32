#ifndef GPIO_H_
#define GPIO_H_

#include "../Application/std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define NUM_OF_PORTS           4
#define NUM_OF_PINS_PER_PORT   8

#define PORTA_ID               0
#define PORTB_ID               1
#define PORTC_ID               2
#define PORTD_ID               3

// Keypad row and column definitions
#define KEYPAD_ROW_PORT        PORTA_ID
#define KEYPAD_ROW_START_PIN   0
#define KEYPAD_ROW_END_PIN     3

#define KEYPAD_COL_PORT        PORTA_ID
#define KEYPAD_COL_START_PIN   4
#define KEYPAD_COL_END_PIN     7

// Servo PWM pin definition
#define SERVO_PWM_PIN          PORTD_ID  // OC1A pin is typically on PB1 for ATmega32

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum
{
	PIN_INPUT,PIN_OUTPUT
}GPIO_PinDirectionType;

typedef enum
{
	PORT_INPUT,PORT_OUTPUT=0xFF
}GPIO_PortDirectionType;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
void GPIO_setupPinDirection(uint8 port_num, uint8 pin_num, GPIO_PinDirectionType direction);
void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value);
uint8 GPIO_readPin(uint8 port_num, uint8 pin_num);
void GPIO_setupPortDirection(uint8 port_num, uint8 direction);
void GPIO_writePort(uint8 port_num, uint8 value);
uint8 GPIO_readPort(uint8 port_num);

#endif /* GPIO_H_ */