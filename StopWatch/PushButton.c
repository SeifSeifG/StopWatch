/**
 * @file PushButton.c
 * @brief Implementation of push button handling functions for AVR microcontrollers.
 *        Supports external pull-down and internal pull-up configurations.
 */

#include "PushButton.h"

/**
 * @brief Initializes a push button.
 *
 * Sets the button pin as input and enables internal pull-up if specified.
 *
 * @param button Pointer to the PushButton struct instance.
 * @param port Character representing the port ('A' to 'D').
 * @param pin Pin number (0–7).
 * @param type Button type: PULL_DOWN or INTERNAL_PULL_UP.
 */
void PushButton_Init(PushButton* button, uint8 port, uint8 pin, ButtonType type)
{
	button->port = port;
	button->pin  = pin;
	button->type = type;

	SetPin(port, pin, INPUT); // Set as input

	// Enable internal pull-up if needed
	switch (port)
	{
	case 'A':
		if (type == INTERNAL_PULL_UP) SET(PORTA, pin);
		break;
	case 'B':
		if (type == INTERNAL_PULL_UP) SET(PORTB, pin);
		break;
	case 'C':
		if (type == INTERNAL_PULL_UP) SET(PORTC, pin);
		break;
	case 'D':
		if (type == INTERNAL_PULL_UP) SET(PORTD, pin);
		break;
	}
}

/**
 * @brief Reads the current state of the button.
 *
 * Handles both pull-down and internal pull-up configurations and returns a logical state.
 *
 * @param button Pointer to the initialized PushButton struct.
 * @return uint8 Returns PRESSED or RELEASED.
 */
uint8 ReadButton(PushButton* button)
{
	uint8 PinBinaryState = ReadPin(button->port, button->pin);
	uint8 ButtonReading = RELEASED;

	switch (button->type)
	{
	case PULL_DOWN:
		ButtonReading = (PinBinaryState == HIGH) ? PRESSED : RELEASED;
		break;
	default: // INTERNAL_PULL_UP
		ButtonReading = (PinBinaryState == LOW) ? PRESSED : RELEASED;
		break;
	}
	return ButtonReading;
}
