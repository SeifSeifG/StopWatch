/**
 * @file SevenSegment.c
 * @brief Implementation for handling 7-segment display using GPIO on AVR.
 */

#include "SevenSegment.h"

/**
 * @brief Initializes a 7-segment display object.
 *
 * Configures the specified data pins as output. Supports both adjacent and non-adjacent pin configurations.
 *
 * @param mySeg Pointer to the SevenSegment struct to initialize.
 * @param dataPort Port character ('A', 'B', 'C', or 'D') used for data lines.
 * @param dataPins Bitmask indicating which pins on the port are used (e.g., 0x0F for pins 0–3).
 */
void SevenSegment_Init(SevenSegment* mySeg, uint8 dataPort, uint8 dataPins)
{
	mySeg->dataPort = dataPort;
	mySeg->dataMusk = dataPins;

	// Extract and store pin numbers from bitmask
	for (int i = 0, j = 0; i < REGISTER_SIZE; i++)
	{
		if (dataPins & (1 << i))
		{
			mySeg->dataPins[j++] = i;
		}
	}

	// Set each of the data pins as output
	for (int i = 0; i < NUM_DATA_PINS; i++)
	{
		SetPin(mySeg->dataPort, mySeg->dataPins[i], OUTPUT);
	}

	WriteSevenSegment(mySeg, 0); // Display 0 initially
}

/**
 * @brief Displays a 4-bit binary number (0–15) on a 7-segment display.
 *
 * This function assumes a BCD-to-7-segment decoder is connected to the pins.
 *
 * @param mySeg Pointer to the initialized SevenSegment struct.
 * @param data 4-bit number to display (usually 0–9 for digits).
 */
void WriteSevenSegment(SevenSegment* mySeg, uint8 data)
{
	for (int i = 0; i < NUM_DATA_PINS; i++)
	{
		WritePin(mySeg->dataPort, mySeg->dataPins[i], (data & (1 << i)) ? HIGH : LOW);
	}
}
