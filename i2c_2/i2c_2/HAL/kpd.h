#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "../Application/std_types.h"

#define KEYPAD_ROWS    4
#define KEYPAD_COLS    4

// Function to initialize keypad
void KEYPAD_init(void);

// Function to get pressed key
uint8 KEYPAD_getPressedKey(void);

#endif /* KEYPAD_H_ */