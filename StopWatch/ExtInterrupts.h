/**
 * @file external_interrupts.h
 * @author Abdelrahman Samir
 * @date 2025-06-16
 * @brief External interrupt driver interface for AVR (e.g., ATmega32).
 *
 * This header file provides an abstraction for configuring and using
 * external interrupts (INT0, INT1, INT2) on AVR microcontrollers.
 * It supports runtime trigger transition configuration.
 */

#include "DEFS.h"
#include "GPIO.h"

#ifndef EXTERNAL_INTERRUPTS_H
#define EXTERNAL_INTERRUPTS_H

/* Example ISR usage (copy and paste in application file):
 * ISR(INT0_vect) { // your code goes here }
 * ISR(INT1_vect) { // your code goes here }
 * ISR(INT2_vect) { // your code goes here }
 */

/**
 * @brief Enumeration for interrupt trigger types.
 */
typedef enum
{
	LOW_LEVEL,     /**< Trigger on low level */
	EDGE_CHANGE,   /**< Trigger on logical change (only for INT0 and INT1) */
	FALLING_EDGE,  /**< Trigger on falling edge */
	RISING_EDGE    /**< Trigger on rising edge */
} TriggerType;

/**
 * @brief Initialize INT0 with specified trigger type.
 *
 * @param type Trigger type (LOW_LEVEL, EDGE_CHANGE, FALLING_EDGE, RISING_EDGE)
 */
void INT0_Init(TriggerType type);

/**
 * @brief Initialize INT1 with specified trigger type.
 *
 * @param type Trigger type (LOW_LEVEL, EDGE_CHANGE, FALLING_EDGE, RISING_EDGE)
 */
void INT1_Init(TriggerType type);

/**
 * @brief Initialize INT2 with specified trigger type.
 *
 * @param type Trigger type (only FALLING_EDGE or RISING_EDGE supported on INT2)
 */
void INT2_Init(TriggerType type);

/**
 * @brief Change trigger type for INT0 during runtime.
 *
 * @param type New trigger type.
 */
void INT0_RunTimeTransition(TriggerType type);

/**
 * @brief Change trigger type for INT1 during runtime.
 *
 * @param type New trigger type.
 */
void INT1_RunTimeTransition(TriggerType type);

/**
 * @brief Change trigger type for INT2 during runtime.
 *
 * @param type New trigger type.
 */
void INT2_RunTimeTransition(TriggerType type);

#endif // EXTERNAL_INTERRUPTS_H
