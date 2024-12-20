#include "kpd.h"
#include "../MCAL/gpio.h"
#include <util/delay.h>

// Keypad layout
static const uint8 KEYPAD_MAP[KEYPAD_ROWS][KEYPAD_COLS] = {
	{'1','2','3','A'},
	{'4','5','6','B'},
	{'7','8','9','C'},
	{'*','0','#','D'}
};

void KEYPAD_init(void)
{
	// Configure row pins as input with pull-up
	for(uint8 i = 0; i < KEYPAD_ROWS; i++)
	{
		GPIO_setupPinDirection(KEYPAD_ROW_PORT, KEYPAD_ROW_START_PIN + i, PIN_INPUT);
		GPIO_writePin(KEYPAD_ROW_PORT, KEYPAD_ROW_START_PIN + i, LOGIC_HIGH);
	}
	
	// Configure column pins as output, initially high
	for(uint8 i = 0; i < KEYPAD_COLS; i++)
	{
		GPIO_setupPinDirection(KEYPAD_COL_PORT, KEYPAD_COL_START_PIN + i, PIN_OUTPUT);
		GPIO_writePin(KEYPAD_COL_PORT, KEYPAD_COL_START_PIN + i, LOGIC_HIGH);
	}
}

uint8 KEYPAD_getPressedKey(void)
{
	while(1)
	{
		for(uint8 col = 0; col < KEYPAD_COLS; col++)
		{
			// Deactivate all columns
			GPIO_writePort(KEYPAD_COL_PORT, 0xFF);
			
			// Activate current column
			GPIO_writePin(KEYPAD_COL_PORT, KEYPAD_COL_START_PIN + col, LOGIC_LOW);
			
			// Check rows
			for(uint8 row = 0; row < KEYPAD_ROWS; row++)
			{
				if(GPIO_readPin(KEYPAD_ROW_PORT, KEYPAD_ROW_START_PIN + row) == LOGIC_LOW)
				{
					// Debounce
					_delay_ms(50);
					
					// Wait for key release
					while(GPIO_readPin(KEYPAD_ROW_PORT, KEYPAD_ROW_START_PIN + row) == LOGIC_LOW);
					
					return KEYPAD_MAP[row][col];
				}
			}
		}
	}
}