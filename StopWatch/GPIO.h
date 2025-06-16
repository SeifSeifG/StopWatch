/**
 * @file gpio.h
 * @author Abdelrahman Samir
 * @date 2025-06-16
 * @brief GPIO (General Purpose Input/Output) driver interface for AVR microcontrollers.
 *
 * This header file provides function declarations for GPIO operations including
 * setting pin/port directions, reading/writing pin values, and toggling states.
 * It is designed for use with 8-bit AVR microcontrollers.
 */

#include "DEFS.h"

#ifndef GPIO_H
#define GPIO_H

/** @brief Number of I/O ports (typically A to D on ATmega32). */
#define NUM_PORTS 4

/** @brief Number of pins per port (8 for 8-bit AVR). */
#define NUM_PINS_PER_PORT 8

/**
 * @brief Enumeration to specify the direction of a pin or port.
 */
typedef enum
{
	INPUT,  /**< Configure pin as input */
	OUTPUT, /**< Configure pin as output */
} Direction;

/**
 * @brief Set the direction of a specific pin in a port.
 *
 * @param port Port number (0 = A, 1 = B, 2 = C, 3 = D).
 * @param pin Pin number (0 to 7).
 * @param direction Direction to set (INPUT or OUTPUT).
 */
void SetPin(uint8 port, uint8 pin, Direction direction);

/**
 * @brief Write a HIGH or LOW value to a specific pin.
 *
 * @param port Port number.
 * @param pin Pin number.
 * @param val Value to write (HIGH or LOW).
 */
void WritePin(uint8 port, uint8 pin, uint8 val);

/**
 * @brief Read the current value of a specific pin.
 *
 * @param port Port number.
 * @param pin Pin number.
 * @return uint8 Current logic level (HIGH or LOW).
 */
uint8 ReadPin(uint8 port, uint8 pin);

/**
 * @brief Toggle the logic level of a specific pin.
 *
 * @param port Port number.
 * @param pin Pin number.
 */
void TogglePin(uint8 port, uint8 pin);

/**
 * @brief Set the direction of an entire port.
 *
 * @param port Port number.
 * @param direction Direction to set (INPUT or OUTPUT).
 */
void SetPort(uint8 port, Direction direction);

/**
 * @brief Write an 8-bit value to an entire port.
 *
 * @param port Port number.
 * @param val Value to write (0–255).
 */
void WritePort(uint8 port, uint8 val);

/**
 * @brief Read the current 8-bit value from a port.
 *
 * @param port Port number.
 * @return uint8 Value of the port (0–255).
 */
uint8 ReadPort(uint8 port);

#endif // GPIO_H
