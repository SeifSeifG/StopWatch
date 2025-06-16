/**
 * @file buzzer.h
 * @author Abdelrahman Samir
 * @date 2025-06-16
 * @brief Buzzer driver interface for AVR microcontrollers.
 *
 * This file provides a simple abstraction to control a digital buzzer
 * connected to a GPIO pin. Functions include initialization, turn-on, and turn-off.
 */

#include "GPIO.h"

#ifndef BUZZER_H
#define BUZZER_H

/**
 * @brief Structure representing a Buzzer connected to a specific GPIO pin.
 */
typedef struct
{
	uint8 port; /**< Port number (0 = A, 1 = B, etc.) */
	uint8 pin;  /**< Pin number (0 to 7) */
} Buzzer;

/**
 * @brief Initialize the buzzer by setting the corresponding pin as output.
 *
 * @param myBuzzer Pointer to the Buzzer struct to initialize.
 * @param port Port number.
 * @param pin Pin number.
 */
void Buzzer_Init(Buzzer* myBuzzer, uint8 port, uint8 pin);

/**
 * @brief Activate (turn on) the buzzer.
 *
 * @param myBuzzer Pointer to the Buzzer struct.
 */
void BuzzerOn(Buzzer* myBuzzer);

/**
 * @brief Deactivate (turn off) the buzzer.
 *
 * @param myBuzzer Pointer to the Buzzer struct.
 */
void BuzzerOff(Buzzer* myBuzzer);

#endif // BUZZER_H
