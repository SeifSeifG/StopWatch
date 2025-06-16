/**
 * @file led.h
 * @author Abdelrahman Samir
 * @date 2025-06-16
 * @brief LED driver interface for AVR microcontrollers.
 *
 * This file provides a simple abstraction for handling LEDs connected
 * to GPIO pins. It supports both positive and negative logic configurations.
 */

#include "GPIO.h"

#ifndef LED_H
#define LED_H

/**
 * @brief Enumeration for LED logic type.
 */
typedef enum
{
	POSITIVE_LOGIC, /**< LED is ON when pin is HIGH */
	NEGATIVE_LOGIC  /**< LED is ON when pin is LOW */
} LedType;

/**
 * @brief Structure representing an LED connected to a specific GPIO pin.
 */
typedef struct
{
	uint8 port;     /**< Port number (0 = A, 1 = B, etc.) */
	uint8 pin;      /**< Pin number (0 to 7) */
	LedType type;   /**< Logic type (positive or negative) */
} Led;

/**
 * @brief Initialize an LED with given port, pin, and logic type.
 *
 * @param myLED Pointer to the Led struct to initialize.
 * @param port Port number.
 * @param pin Pin number.
 * @param type Logic type (POSITIVE_LOGIC or NEGATIVE_LOGIC).
 */
void Led_Init(Led* myLED, uint8 port, uint8 pin, LedType type);

/**
 * @brief Turn ON the specified LED.
 *
 * @param myLED Pointer to the Led struct.
 */
void TurnOnLed(Led* myLED);

/**
 * @brief Turn OFF the specified LED.
 *
 * @param myLED Pointer to the Led struct.
 */
void TurnOffLed(Led* myLED);

/**
 * @brief Toggle the current state of the specified LED.
 *
 * @param myLED Pointer to the Led struct.
 */
void ToggleLed(Led* myLED);

#endif // LED_H
