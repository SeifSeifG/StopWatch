/**
 * @file GPIO.c
 * @brief GPIO control functions for AVR microcontrollers (ATmega32).
 *        Provides pin and port manipulation: set direction, write, read, and toggle.
 * @author Seif
 * @date 2025-06-16
 */

#include "GPIO.h"

/**
 * @brief Sets the direction of a specific pin.
 * @param port Character representing the port ('A' to 'D').
 * @param pin Pin number (0–7).
 * @param direction Either OUTPUT or INPUT.
 */
void SetPin(uint8 port, uint8 pin, Direction direction)
{
	if (pin > (NUM_PINS_PER_PORT - 1)) return;

	switch (port)
	{
	case 'A': direction == OUTPUT ? SET(DDRA, pin) : CLEAR(DDRA, pin); break;
	case 'B': direction == OUTPUT ? SET(DDRB, pin) : CLEAR(DDRB, pin); break;
	case 'C': direction == OUTPUT ? SET(DDRC, pin) : CLEAR(DDRC, pin); break;
	case 'D': direction == OUTPUT ? SET(DDRD, pin) : CLEAR(DDRD, pin); break;
	}
}

/**
 * @brief Writes a value to a pin.
 * @param port Port name ('A' to 'D').
 * @param pin Pin number (0–7).
 * @param val Value to write: HIGH or LOW.
 */
void WritePin(uint8 port, uint8 pin, uint8 val)
{
	if (pin > (NUM_PINS_PER_PORT - 1)) return;

	switch (port)
	{
	case 'A': val == HIGH ? SET(PORTA, pin) : CLEAR(PORTA, pin); break;
	case 'B': val == HIGH ? SET(PORTB, pin) : CLEAR(PORTB, pin); break;
	case 'C': val == HIGH ? SET(PORTC, pin) : CLEAR(PORTC, pin); break;
	case 'D': val == HIGH ? SET(PORTD, pin) : CLEAR(PORTD, pin); break;
	}
}

/**
 * @brief Reads the digital level of a pin.
 * @param port Port name ('A' to 'D').
 * @param pin Pin number (0–7).
 * @return uint8 Returns HIGH or LOW depending on the pin state.
 */
uint8 ReadPin(uint8 port, uint8 pin)
{
	uint8 pinValue = LOW;

	if (pin > (NUM_PINS_PER_PORT - 1)) return pinValue;

	switch (port)
	{
	case 'A': pinValue = IS_SET(PINA, pin) ? HIGH : LOW; break;
	case 'B': pinValue = IS_SET(PINB, pin) ? HIGH : LOW; break;
	case 'C': pinValue = IS_SET(PINC, pin) ? HIGH : LOW; break;
	case 'D': pinValue = IS_SET(PIND, pin) ? HIGH : LOW; break;
	}

	return pinValue;
}

/**
 * @brief Toggles the value of a pin.
 * @param port Port name ('A' to 'D').
 * @param pin Pin number (0–7).
 */
void TogglePin(uint8 port, uint8 pin)
{
	if (pin > (NUM_PINS_PER_PORT - 1)) return;

	switch (port)
	{
	case 'A': TOGGLE(PORTA, pin); break;
	case 'B': TOGGLE(PORTB, pin); break;
	case 'C': TOGGLE(PORTC, pin); break;
	case 'D': TOGGLE(PORTD, pin); break;
	}
}

/**
 * @brief Sets the direction of all 8 pins of a port.
 * @param port Port name ('A' to 'D').
 * @param direction OUTPUT to set all pins as outputs, INPUT for all inputs.
 */
void SetPort(uint8 port, Direction direction)
{
	switch (port)
	{
	case 'A': DDRA = (direction == OUTPUT) ? 0xFF : 0x00; break;
	case 'B': DDRB = (direction == OUTPUT) ? 0xFF : 0x00; break;
	case 'C': DDRC = (direction == OUTPUT) ? 0xFF : 0x00; break;
	case 'D': DDRD = (direction == OUTPUT) ? 0xFF : 0x00; break;
	}
}

/**
 * @brief Writes a value to an entire port (8 pins).
 * @param port Port name ('A' to 'D').
 * @param val HIGH to set all pins, LOW to clear all pins.
 */
void WritePort(uint8 port, uint8 val)
{
	switch (port)
	{
	case 'A': PORTA = (val == HIGH) ? 0xFF : 0x00; break;
	case 'B': PORTB = (val == HIGH) ? 0xFF : 0x00; break;
	case 'C': PORTC = (val == HIGH) ? 0xFF : 0x00; break;
	case 'D': PORTD = (val == HIGH) ? 0xFF : 0x00; break;
	}
}

/**
 * @brief Reads the current value of an entire port.
 * @param port Port name ('A' to 'D').
 * @return uint8 8-bit value representing the port state.
 */
uint8 ReadPort(uint8 port)
{
	switch (port)
	{
	case 'A': return PORTA;
	case 'B': return PORTB;
	case 'C': return PORTC;
	case 'D': return PORTD;
	default:  return 0x00;
	}
}
