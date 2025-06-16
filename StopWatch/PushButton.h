/**
 * @file push_button.h
 * @author Abdelrahman Samir
 * @date 2025-06-16
 * @brief Push button driver interface for AVR microcontrollers.
 *
 * This header file provides an interface for initializing and reading
 * push button states. It supports different configurations like pull-up,
 * pull-down, and internal pull-up.
 */

#include "GPIO.h"

#ifndef PUSH_BUTTON_H
#define PUSH_BUTTON_H

/** @brief Value returned when button is pressed. */
#define PRESSED  1

/** @brief Value returned when button is released. */
#define RELEASED 0

/**
 * @brief Enumeration for the electrical type of push button.
 */
typedef enum
{
	PULL_DOWN,        /**< External pull-down resistor configuration */
	PULL_UP,          /**< External pull-up resistor configuration */
	INTERNAL_PULL_UP  /**< AVR internal pull-up resistor configuration */
} ButtonType;

/**
 * @brief Structure representing a push button connected to a specific GPIO pin.
 */
typedef struct
{
	uint8 port;       /**< Port number (0 = A, 1 = B, etc.) */
	uint8 pin;        /**< Pin number (0 to 7) */
	ButtonType type;  /**< Electrical type of button */
} PushButton;

/**
 * @brief Initialize a push button by setting pin direction and pull configuration.
 *
 * @param button Pointer to PushButton struct to initialize.
 * @param port Port number where the button is connected.
 * @param pin Pin number where the button is connected.
 * @param type Button configuration type (PULL_DOWN, PULL_UP, INTERNAL_PULL_UP).
 */
void PushButton_Init(PushButton* button, uint8 port, uint8 pin, ButtonType type);

/**
 * @brief Read the current state of a push button.
 *
 * @param button Pointer to the PushButton struct.
 * @return uint8 PRESSED (1) if pressed, RELEASED (0) if not pressed.
 */
uint8 ReadButton(PushButton* button);

#endif // PUSH_BUTTON_H
