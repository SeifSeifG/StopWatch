/**
 * @file Application.c
 * @brief Implements the stopwatch application logic, including time update, display refresh, and ISR handlers.
 * @author Seif
 * @date 2025-06-16
 */

#include "Application.h"

/// Global stopwatch time variable
Time g_SevenSeg_time = { 3, 59,46 };

/// Global mode flag: INCREMENTAL_MODE or DECREMENTAL_MODE
volatile uint8 g_mode = INCREMENTAL_MODE;

/// Array of SevenSegment display instances (HH:MM:SS)
SevenSegment g_Mult_SevenSegment[NUM_SEVEN_SEGMENTS];

/**
 * @brief External interrupt 0 ISR.
 * Resets time and mode.
 */
ISR(INT0_vect)
{
	g_SevenSeg_time.Hour = 0;
	g_SevenSeg_time.Min = 0;
	g_SevenSeg_time.Sec = 0;
	g_mode = INCREMENTAL_MODE;
}

/**
 * @brief External interrupt 1 ISR.
 * Pauses stopwatch by turning off Timer1.
 */
ISR(INT1_vect)
{
	Timer1_OFF();
}

/**
 * @brief External interrupt 2 ISR.
 * Resumes stopwatch by turning on Timer1.
 */
ISR(INT2_vect)
{
	Timer1_ON();
}

/**
 * @brief Timer1 Compare Match A ISR.
 * Increments or decrements seconds depending on mode.
 */
ISR(TIMER1_COMPA_vect)
{
	if (g_mode == INCREMENTAL_MODE)
	{
		IncSec();
	}
	else // DECREMENTAL_MODE
	{
		DecSec();
	}
}

/**
 * @brief Refreshes the seven segment display with the current time.
 */
void SevenSegmentUpdate()
{
	uint8* ptr_to_time = (uint8*)&g_SevenSeg_time;
	for(int i = 0; i < NUM_SEVEN_SEGMENTS; i++)
	{
		// Select current digit
		SET(SEVEN_SEGMENT_MULT_PORT, i);

		if (i & 1) // odd: units digit
		{
			WriteSevenSegment(&g_Mult_SevenSegment[i], (*ptr_to_time) % 10);
			ptr_to_time++;
		}
		else // even: tens digit
		{
			WriteSevenSegment(&g_Mult_SevenSegment[i], (*ptr_to_time) / 10);
		}

		_delay_ms(1);

		// Clear all digit selections
		CLEAR_REG(SEVEN_SEGMENT_MULT_PORT, SEVEN_SEGMENT_MULT_PIN);
	}
}

/**
 * @brief Updates LEDs based on current stopwatch mode.
 * @param countUp Pointer to count-up mode LED.
 * @param countDown Pointer to count-down mode LED.
 */
void UpdateCountLEDs(Led* countUp, Led* countDown)
{
    if (g_mode == INCREMENTAL_MODE)
    {
        TurnOnLed(countUp);
        TurnOffLed(countDown);
    }
    else
    {
        TurnOnLed(countDown);
        TurnOffLed(countUp);
    }
}

/**
 * @brief Increments the hour value.
 */
void IncHour()
{
	if (g_SevenSeg_time.Hour == 99)
	{
		g_SevenSeg_time.Hour = 99;
		g_SevenSeg_time.Min = 59;
		g_SevenSeg_time.Sec = 59;
	}
	else
	{
		g_SevenSeg_time.Hour++;
	}
}

/**
 * @brief Decrements the hour value.
 */
void DecHour()
{
	if (g_SevenSeg_time.Hour == 0)
	{
		g_SevenSeg_time.Hour = 0;
		g_SevenSeg_time.Min = 0;
		g_SevenSeg_time.Sec = 0;
	}
	else
	{
		g_SevenSeg_time.Hour--;
	}
}

/**
 * @brief Increments the minute value and wraps to hour if needed.
 */
void IncMin()
{
	if (g_SevenSeg_time.Min == 59)
	{
		g_SevenSeg_time.Min = 0;
		IncHour();
	}
	else
	{
		g_SevenSeg_time.Min++;
	}
}

/**
 * @brief Decrements the minute value and wraps from hour if needed.
 */
void DecMin()
{
	if (g_SevenSeg_time.Min == 0)
	{
		g_SevenSeg_time.Min = 59;
		DecHour();
	}
	else
	{
		g_SevenSeg_time.Min--;
	}
}

/**
 * @brief Increments the second value and wraps to minute if needed.
 */
void IncSec()
{
	if (g_SevenSeg_time.Sec == 59)
	{
		g_SevenSeg_time.Sec = 0;
		IncMin();
	}
	else
	{
		g_SevenSeg_time.Sec++;
	}
}

/**
 * @brief Decrements the second value and wraps from minute if needed.
 */
void DecSec()
{
	if (g_SevenSeg_time.Sec == 0)
	{
		g_SevenSeg_time.Sec = 59;
		DecMin();
	}
	else
	{
		g_SevenSeg_time.Sec--;
	}
}
