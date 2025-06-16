/**
 * @file ExtInterrupts.c
 * @brief Implementation of external interrupt initialization and runtime reconfiguration.
 */

#include "ExtInterrupts.h"

/**
 * @brief Initializes INT0 with a specified trigger type.
 *
 * Sets PD2 as input and configures INT0 edge/level sensitivity.
 *
 * @param type Trigger condition (LOW_LEVEL, EDGE_CHANGE, FALLING_EDGE, RISING_EDGE)
 */
void INT0_Init(TriggerType type)
{
	cli(); // Disable global interrupts

	CLEAR(DDRD, PD2); // Set PD2 as input
	SET(GICR, INT0);  // Enable INT0

	switch(type)
	{
	case LOW_LEVEL:
		MCUCR &= ~((1 << ISC00) | (1 << ISC01));
		break;
	case EDGE_CHANGE:
		SET(MCUCR, ISC01);
		CLEAR(MCUCR, ISC00);
		break;
	case FALLING_EDGE:
		CLEAR(MCUCR, ISC01);
		SET(MCUCR, ISC00);
		break;
	case RISING_EDGE:
		MCUCR |= ((1 << ISC00) | (1 << ISC01));
		break;
	}

	sei(); // Re-enable global interrupts
}

/**
 * @brief Initializes INT1 with a specified trigger type.
 *
 * Sets PD3 as input and configures INT1 edge/level sensitivity.
 *
 * @param type Trigger condition.
 */
void INT1_Init(TriggerType type)
{
	cli();

	DDRD &= ~(1 << PD3);
	GICR |= (1 << INT1);

	switch(type)
	{
	case LOW_LEVEL:
		MCUCR &= ~((1 << ISC10) | (1 << ISC11));
		break;
	case EDGE_CHANGE:
		MCUCR |= (1 << ISC11);
		MCUCR &= ~(1 << ISC10);
		break;
	case FALLING_EDGE:
		MCUCR &= ~(1 << ISC11);
		MCUCR |= (1 << ISC10);
		break;
	case RISING_EDGE:
		MCUCR |= ((1 << ISC10) | (1 << ISC11));
		break;
	}

	sei();
}

/**
 * @brief Initializes INT2 with a specified trigger type (falling or rising).
 *
 * @param type Trigger condition.
 */
void INT2_Init(TriggerType type)
{
	cli();

	DDRB &= ~(1 << PB2);
	GICR |= (1 << INT2);

	switch(type)
	{
	case FALLING_EDGE:
		MCUCSR &= ~(1 << ISC2);
		break;
	case RISING_EDGE:
		MCUCSR |= (1 << ISC2);
		break;
	default:
		break;
	}

	sei();
}

/**
 * @brief Dynamically changes INT0 trigger condition during runtime.
 *
 * Disables INT0, updates sensitivity, clears interrupt flag, and re-enables INT0.
 *
 * @param type New trigger type to apply.
 */
void INT0_RunTimeTransition(TriggerType type)
{
	cli();

	GICR &= ~(1 << INT0); // Disable INT0

	switch(type)
	{
	case LOW_LEVEL:
		MCUCR &= ~((1 << ISC00) | (1 << ISC01));
		break;
	case EDGE_CHANGE:
		MCUCR |= (1 << ISC01);
		MCUCR &= ~(1 << ISC00);
		break;
	case FALLING_EDGE:
		MCUCR &= ~(1 << ISC01);
		MCUCR |= (1 << ISC00);
		break;
	case RISING_EDGE:
		MCUCR |= ((1 << ISC00) | (1 << ISC01));
		break;
	}

	GIFR |= (1 << INTF0); // Clear INT0 flag
	GICR |= (1 << INT0);  // Re-enable INT0

	sei();
}

/**
 * @brief Dynamically changes INT1 trigger condition during runtime.
 *
 * @param type New trigger type to apply.
 */
void INT1_RunTimeTransition(TriggerType type)
{
	cli();

	GICR &= ~(1 << INT1); // Disable INT1

	switch(type)
	{
	case LOW_LEVEL:
		MCUCR &= ~((1 << ISC10) | (1 << ISC11));
		break;
	case EDGE_CHANGE:
		MCUCR |= (1 << ISC11);
		MCUCR &= ~(1 << ISC10);
		break;
	case FALLING_EDGE:
		MCUCR &= ~(1 << ISC11);
		MCUCR |= (1 << ISC10);
		break;
	case RISING_EDGE:
		MCUCR |= ((1 << ISC10) | (1 << ISC11));
		break;
	}

	GIFR |= (1 << INTF1); // Clear INT1 flag
	GICR |= (1 << INT1);  // Re-enable INT1

	sei();
}

/**
 * @brief Dynamically changes INT2 trigger condition during runtime.
 *
 * @param type New trigger type to apply.
 */
void INT2_RunTimeTransition(TriggerType type)
{
	cli();

	GICR &= ~(1 << INT2); // Disable INT2

	switch(type)
	{
	case FALLING_EDGE:
		MCUCSR &= ~(1 << ISC2);
		break;
	case RISING_EDGE:
		MCUCSR |= (1 << ISC2);
		break;
	default:
		break;
	}

	GIFR |= (1 << INTF2); // Clear INT2 flag
	GICR |= (1 << INT2);  // Re-enable INT2

	sei();
}
