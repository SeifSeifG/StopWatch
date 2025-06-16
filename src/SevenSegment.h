/**
 * @file seven_segment.h
 * @author Abdelrahman Samir
 * @date 2025-06-16
 * @brief Seven-segment display driver interface for AVR microcontrollers.
 *
 * This header provides an abstraction for interfacing with a 4-bit BCD seven-segment display
 * using configurable data pins on a single GPIO port.
 */

#include "GPIO.h"

#ifndef SEVEN_SEGMENT_H
#define SEVEN_SEGMENT_H

/** @brief Number of data pins used (for 4-bit BCD). */
#define NUM_DATA_PINS 4

/**
 * @brief Structure representing a seven-segment display module.
 */
typedef struct
{
	uint8 dataPort;                   /**< Pointer to the data PORT register */
	uint8 dataPins[NUM_DATA_PINS];     /**< Array of pin numbers used for data (4-bit BCD) */
	uint8 dataMusk;                    /**< Bitmask representing active data pins */
} SevenSegment;

/**
 * @brief Initialize a seven-segment display structure.
 *
 * @param mySeg Pointer to the SevenSegment struct to initialize.
 * @param dataPort Port number where data pins are connected (0 = A, 1 = B, etc.).
 * @param dataPins A packed byte where the lower nibble (4 bits) represents the data pins (e.g., 0xE1 = P0, P5, P6, P7).
 */
void SevenSegment_Init(SevenSegment* mySeg, uint8 dataPort, uint8 dataPins);

/**
 * @brief Write a 4-bit value (0–9) to the seven-segment display.
 *
 * @param mySeg Pointer to the SevenSegment struct.
 * @param data BCD digit (0–9) to display.
 */
void WriteSevenSegment(SevenSegment* mySeg, uint8 data);

#endif // SEVEN_SEGMENT_H
