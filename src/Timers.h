/**
 * @file timers.h
 * @author Abdelrahman Samir
 * @date 2025-06-16
 * @brief Timer driver interface for AVR microcontrollers (e.g., ATmega32).
 *
 * This file provides initialization functions and control utilities
 * for Timer0, Timer1, and Timer2 in various modes including Normal and CTC.
 */
#include "DEFS.h"
#include <avr/interrupt.h>

#ifndef TIMERS_H
#define TIMERS_H

/* Example ISR usage (copy and paste in application file):
ISR(TIMER0_OVF_vect)
ISR(TIMER0_COMP_vect)
ISR(TIMER1_OVF_vect)    // Timer1 Overflow mode
ISR(TIMER1_COMPA_vect)  // Timer1 Compare Match A (OCR1A
ISR(TIMER1_COMPB_vect)  // Timer1 Compare Match B (OCR1B
ISR(TIMER2_OVF_vect)
ISR(TIMER2_COMP_vect)
*/


/**
 * @brief Timer identifier enumeration.
 */
typedef enum
{
	Timer0, /**< 8-bit Timer0 */
	Timer1, /**< 16-bit Timer1 */
	Timer2  /**< 8-bit Timer2 */
} Timer;

/**
 * @brief Timer operating modes.
 */
typedef enum
{
	NORMAL,     /**< Normal counting mode */
	PWM,        /**< Phase-correct PWM mode */
	CTC,        /**< Clear Timer on Compare match */
	FAST_PWM    /**< Fast PWM mode */
} TimerMode;

/**
 * @brief Clock source and prescaler settings.
 */
typedef enum
{
	NO_PRESCALAR,      /**< No prescaling (clk/1) */
	PRESCALAR_8,       /**< clk/8 */
	PRESCALAR_64,      /**< clk/64 */
	PRESCALAR_256,     /**< clk/256 */
	PRESCALAR_1024,    /**< clk/1024 */
	EXT_FALLING_EDGE,  /**< External clock source on falling edge */
	EXT_RISING_EDGE    /**< External clock source on rising edge */
} TimerSetting;

/**
 * @brief Timer operation technique (polling or interrupt).
 */
typedef enum
{
	POLLING,   /**< Busy wait method */
	INTERRUPT  /**< ISR-based operation */
} TimerTechnique;

/**
 * @brief Initialize Timer0 in Normal mode.
 *
 * @param preScalar Timer prescaler setting.
 * @param tech Timer operation method (polling or interrupt).
 */
void Timer0_Normal_Init(TimerSetting preScalar, TimerTechnique tech);

/**
 * @brief Initialize Timer1 in Normal mode.
 *
 * @param preScalar Timer prescaler setting.
 * @param tech Timer operation method (polling or interrupt).
 */
void Timer1_Normal_Init(TimerSetting preScalar, TimerTechnique tech);

/**
 * @brief Initialize Timer2 in Normal mode.
 *
 * @param preScalar Timer prescaler setting.
 * @param tech Timer operation method (polling or interrupt).
 */
void Timer2_Normal_Init(TimerSetting preScalar, TimerTechnique tech);

/**
 * @brief Initialize Timer0 in CTC (Compare Match) mode.
 *
 * @param compareVal Value to compare against the counter.
 * @param preScalar Timer prescaler setting.
 */
void Timer0_CTC_Init(uint8 compareVal, TimerSetting preScalar);

/**
 * @brief Initialize Timer1 in CTC (Compare Match) mode.
 *
 * @param compareVal Value to compare against the counter (16-bit).
 * @param preScalar Timer prescaler setting.
 */
void Timer1_CTC_Init(uint16 compareVal, TimerSetting preScalar);

/**
 * @brief Initialize Timer2 in CTC (Compare Match) mode.
 *
 * @param compareVal Value to compare against the counter.
 * @param preScalar Timer prescaler setting.
 */
void Timer2_CTC_Init(uint8 compareVal, TimerSetting preScalar);

/**
 * @brief Disable Timer0 (stops counting).
 */
void Timer0_OFF();

/**
 * @brief Enable Timer0 (resumes counting).
 */
void Timer0_ON();

/**
 * @brief Disable Timer1 (stops counting).
 */
void Timer1_OFF();

/**
 * @brief Enable Timer1 (resumes counting).
 */
void Timer1_ON();

/**
 * @brief Disable Timer2 (stops counting).
 */
void Timer2_OFF();

/**
 * @brief Enable Timer2 (resumes counting).
 */
void Timer2_ON();

#endif // TIMERS_H
