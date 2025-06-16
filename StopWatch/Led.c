/**
 * @file Led.c
 * @brief Implementation of basic LED control functions using GPIO.
 */

#include "Led.h"

/**
 * @brief Initializes an LED with a given logic type and sets it as output.
 *
 * This function sets the direction of the corresponding pin and ensures the LED is turned off initially.
 *
 * @param myLed Pointer to the Led structure.
 * @param port Port where the LED is connected ('A', 'B', 'C', or 'D').
 * @param pin Pin number (0–7) for the LED.
 * @param type LED logic type (POSITIVE_LOGIC or NEGATIVE_LOGIC).
 */
void Led_Init(Led* myLed, uint8 port, uint8 pin, LedType type)
{
	myLed->port = port;
	myLed->pin = pin;
	myLed->type = type;

	SetPin(port, pin, OUTPUT);
	TurnOffLed(myLed);
}

/**
 * @brief Turns on the LED.
 *
 * Handles positive and negative logic configurations accordingly.
 *
 * @param myLed Pointer to the initialized Led structure.
 */
void TurnOnLed(Led* myLed)
{
	switch(myLed->type)
	{
	case POSITIVE_LOGIC:
		WritePin(myLed->port, myLed->pin, HIGH);
		break;
	case NEGATIVE_LOGIC:
		WritePin(myLed->port, myLed->pin, LOW);
		break;
	}
}

/**
 * @brief Turns off the LED.
 *
 * Handles positive and negative logic configurations accordingly.
 *
 * @param myLed Pointer to the initialized Led structure.
 */
void TurnOffLed(Led* myLed)
{
	switch(myLed->type)
	{
	case POSITIVE_LOGIC:
		WritePin(myLed->port, myLed->pin, LOW);
		break;
	case NEGATIVE_LOGIC:
		WritePin(myLed->port, myLed->pin, HIGH);
		break;
	}
}

/**
 * @brief Toggles the LED state.
 *
 * Independently of logic type, toggles the current state of the LED pin.
 *
 * @param myLED Pointer to the initialized Led structure.
 */
void ToggleLed(Led* myLED)
{
	TogglePin(myLED->port, myLED->pin);
}
