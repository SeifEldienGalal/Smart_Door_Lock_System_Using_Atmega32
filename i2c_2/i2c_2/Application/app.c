#include "../HAL/lcd_I2C.h"
#include "../HAL/kpd.h"
#include "../HAL/servo.h"
#include "../MCAL/gpio.h"
#include <util/delay.h>

#define RESET_BUTTON_PORT     PORTB_ID
#define RESET_BUTTON_PIN      PIN0_ID  // Using PB0 as the reset button

#define PASSWORD_LENGTH 4
#define MAX_ATTEMPTS 3
#define LOCKOUT_TIME 30
#define DOOR_OPEN_ANGLE 90
#define DOOR_CLOSE_ANGLE 0

const uint8 CORRECT_PASSWORD[PASSWORD_LENGTH] = {'1','2','3','4'};

uint8 verifyPassword(uint8 *entered_pwd)
{
	for(uint8 i = 0; i < PASSWORD_LENGTH; i++)
	{
		if(entered_pwd[i] != CORRECT_PASSWORD[i])
		return FALSE;
	}
	return TRUE;
}

// Function to initialize reset button
void RESET_BUTTON_init(void)
{
	// Configure reset button pin as input with pull-up
	GPIO_setupPinDirection(RESET_BUTTON_PORT, RESET_BUTTON_PIN, PIN_INPUT);
	GPIO_writePin(RESET_BUTTON_PORT, RESET_BUTTON_PIN, LOGIC_HIGH);
}

// Function to check reset button
uint8 RESET_BUTTON_isPressed(void)
{
	return (GPIO_readPin(RESET_BUTTON_PORT, RESET_BUTTON_PIN) == LOGIC_LOW);
}

int main(void)
{
	uint8 attempts = 0;
	uint8 password[PASSWORD_LENGTH];
	
	// Initialize peripherals
	LCD_init();
	KEYPAD_init();
	SERVO_init();
	RESET_BUTTON_init();
	
	while(1)
	{
		// Reset password entry
		for(uint8 i = 0; i < PASSWORD_LENGTH; i++)
		password[i] = 0;
		
		// Display password prompt
		LCD_clearScreen();
		LCD_displayString("Enter Password:");
		LCD_moveCursor(1, 0);
		
		// Collect password
		for(uint8 i = 0; i < PASSWORD_LENGTH; i++)
		{
			password[i] = KEYPAD_getPressedKey();
			LCD_displayCharacter('*');
		}
		
		// Verify password
		if(verifyPassword(password))
		{
			// Access granted
			LCD_clearScreen();
			LCD_displayString("Access Granted!");
			
			// Open door
			SERVO_setAngle(DOOR_OPEN_ANGLE);
			_delay_ms(5000);  // Wait 5 seconds
			
			// Reset attempts
			attempts = 0;
			
			// Wait for user interaction
			while(1)
			{
				// Check reset button
				if(RESET_BUTTON_isPressed())
				{
					// Debounce
					_delay_ms(50);
					
					// Wait for button release
					while(RESET_BUTTON_isPressed());
					
					// Close door
					LCD_clearScreen();
					LCD_displayString("Door Closing...");
					SERVO_setAngle(DOOR_CLOSE_ANGLE);
					_delay_ms(1000);
					break;  // Return to main password entry loop
				}
			}
		}
		else
		{
			// Access denied
			attempts++;
			
			if(attempts >= MAX_ATTEMPTS)
			{
				// Lockout
				LCD_clearScreen();
				LCD_displayString("Locked Out!");
				LCD_moveCursor(1, 0);
				LCD_displayString("Wait 30 seconds");
				
				// Wait 30 seconds
				for(uint8 i = 0; i < LOCKOUT_TIME; i++)
				_delay_ms(1000);
				
				// Reset attempts
				attempts = 0;
			}
			else
			{
				// Show attempts left
				LCD_clearScreen();
				LCD_displayString("Wrong Password!");
				LCD_moveCursor(1, 0);
				LCD_intgerToString(MAX_ATTEMPTS - attempts);
				LCD_displayString(" attempts left");
				_delay_ms(2000);
			}
		}
	}
	
	return 0;
}