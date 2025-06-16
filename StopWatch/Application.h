/**
 * @file ApplicationDefinitions.h
 * @author Abdelrahman Samir
 * @date 2025-06-16
 * @brief Definitions and configuration macros for stopwatch application components.
 *
 * This file centralizes the configuration for I/O pins, modes, and global variables
 * used throughout the stopwatch project.
 */

#ifndef APPLICATION
#define APPLICATION

#include "SevenSegment.h"
#include "PushButton.h"
#include "Buzzer.h"
#include "Led.h"
#include "ExtInterrupts.h"
#include "Timers.h"

/** @name Button Definitions
 *  Macros defining each push button's port, pin, and pull configuration.
 */
///@{
#define RESET_BB_PIN PD2
#define RESET_BB_PORT 'D'
#define RESET_BB_TYPE INTERNAL_PULL_UP

#define RESUME_BB_PIN PB2
#define RESUME_BB_PORT 'B'
#define RESUME_BB_TYPE INTERNAL_PULL_UP

#define PAUSE_BB_PIN PD3
#define PAUSE_BB_PORT 'D'
#define PAUSE_BB_TYPE PULL_UP

#define MODE_BB_PIN PB7
#define MODE_BB_PORT 'B'
#define MODE_BB_TYPE INTERNAL_PULL_UP

#define HR_INC_BB_PIN PB1
#define HR_INC_BB_PORT 'B'
#define HR_INC_BB_TYPE INTERNAL_PULL_UP

#define HR_DEC_BB_PIN PB0
#define HR_DEC_BB_PORT 'B'
#define HR_DEC_BB_TYPE INTERNAL_PULL_UP

#define MIN_INC_BB_PIN PB4
#define MIN_INC_BB_PORT 'B'
#define MIN_INC_BB_TYPE INTERNAL_PULL_UP

#define MIN_DEC_BB_PIN PB3
#define MIN_DEC_BB_PORT 'B'
#define MIN_DEC_BB_TYPE INTERNAL_PULL_UP

#define SEC_INC_BB_PIN PB6
#define SEC_INC_BB_PORT 'B'
#define SEC_INC_BB_TYPE INTERNAL_PULL_UP

#define SEC_DEC_BB_PIN PB5
#define SEC_DEC_BB_PORT 'B'
#define SEC_DEC_BB_TYPE INTERNAL_PULL_UP
///@}

/** @name LED and Buzzer Definitions */
///@{
#define COUNT_UP_LED_PORT 'D'
#define COUNT_UP_LED_PIN PD4
#define COUNT_UP_LED_TYPE NEGATIVE_LOGIC

#define COUNT_DOWN_LED_PORT 'D'
#define COUNT_DOWN_LED_PIN PD5
#define COUNT_DOWN_LED_TYPE NEGATIVE_LOGIC

#define BUZZER_PIN PD0
#define BUZZER_PORT 'D'
///@}

/** @name Seven Segment Configuration */
///@{
#define NUM_SEVEN_SEGMENTS 6
#define SEVEN_SEGMENT_DATA_PORT 'C'
#define SEVEN_SEGMENT_DATA_PINS 0x0F
#define SEVEN_SEGMENT_MULT_PORT PORTA
#define SEVEN_SEGMENT_MULT_PIN 0x3F
///@}

/** @name Stopwatch Mode Constants */
///@{
#define DECREMENTAL_MODE 0
#define INCREMENTAL_MODE 1
#define ToggleStopWatchMode ( g_mode ^= (1) )
///@}

/**
 * @brief Compare match value for 1-second tick at 1 MHz CPU frequency and prescaler of 64.
 */
#define COMPARE_MATCH_FOR_1SEC ((uint16)15625)

/**
 * @brief Struct representing a time format (hours, minutes, seconds).
 */
typedef struct
{
	uint8 Hour; /**< Hours (0–23) */
	uint8 Min;  /**< Minutes (0–59) */
	uint8 Sec;  /**< Seconds (0–59) */
} Time;

/// Global stopwatch time.
extern Time g_SevenSeg_time;

/// Current stopwatch mode (incremental or decremental).
extern volatile uint8 g_mode;

/// Array holding seven segment display structures.
extern SevenSegment g_Mult_SevenSegment[NUM_SEVEN_SEGMENTS];

/**
 * @brief Updates the state of count-up and count-down LEDs based on the stopwatch mode.
 * @param countUp Pointer to the count-up LED object.
 * @param countDown Pointer to the count-down LED object.
 */
extern void UpdateCountLEDs(Led* countUp, Led* countDown);

/**
 * @brief Refreshes the seven segment display with current time.
 */
void SevenSegmentUpdate();

/** @name Stopwatch Control Functions */
///@{
void IncHour();
void DecHour();
void IncMin();
void DecMin();
void IncSec();
void DecSec();
///@}

#endif // APPLICATION
