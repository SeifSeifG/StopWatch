/**
 * @file Buzzer.c
 * @brief Provides driver functions for controlling a buzzer via GPIO on AVR.
 */

#include "Buzzer.h"

/**
 * @brief Initializes the buzzer pin.
 *
 * Sets the given pin as output and ensures the buzzer is off initially.
 *
 * @param myBuzzer Pointer to the Buzzer struct to initialize.
 * @param port Character representing the port ('A', 'B', 'C', or 'D').
 * @param pin Pin number (0–7) where the buzzer is connected.
 */
void Buzzer_Init(Buzzer* myBuzzer, uint8 port, uint8 pin)
{
	myBuzzer->port = port;
	myBuzzer->pin = pin;

	SetPin(port, pin, OUTPUT);
	BuzzerOff(myBuzzer);  // Ensure buzzer is off at startup
}

/**
 * @brief Turns the buzzer on.
 *
 * Drives the connected pin high.
 *
 * @param myBuzzer Pointer to an initialized Buzzer struct.
 */
void BuzzerOn(Buzzer* myBuzzer)
{
	WritePin(myBuzzer->port, myBuzzer->pin, HIGH);
}

/**
 * @brief Turns the buzzer off.
 *
 * Drives the connected pin low.
 *
 * @param myBuzzer Pointer to an initialized Buzzer struct.
 */
void BuzzerOff(Buzzer* myBuzzer)
{
	WritePin(myBuzzer->port, myBuzzer->pin, LOW);
}
