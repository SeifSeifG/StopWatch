#include "Application.h"

int main()
{
	// Reset button
	PushButton ResetButton;
	PushButton_Init(&ResetButton, RESET_BB_PORT, RESET_BB_PIN, RESET_BB_TYPE);

	// Pause button
	PushButton PauseButton;
	PushButton_Init(&PauseButton, PAUSE_BB_PORT, PAUSE_BB_PIN, PAUSE_BB_TYPE);

	// Resume button
	PushButton ResumeButton;
	PushButton_Init(&ResumeButton, RESUME_BB_PORT, RESUME_BB_PIN, RESUME_BB_TYPE);

	// Mode Toggle button
	PushButton ModeButton;
	PushButton_Init(&ModeButton, MODE_BB_PORT, MODE_BB_PIN, MODE_BB_TYPE);

	// Hour increment
	PushButton HourIncButton;
	PushButton_Init(&HourIncButton, HR_INC_BB_PORT, HR_INC_BB_PIN, HR_INC_BB_TYPE);

	// Hour decrement
	PushButton HourDecButton;
	PushButton_Init(&HourDecButton, HR_DEC_BB_PORT, HR_DEC_BB_PIN, HR_DEC_BB_TYPE);

	// Minutes increment
	PushButton MinuteIncButton;
	PushButton_Init(&MinuteIncButton, MIN_INC_BB_PORT, MIN_INC_BB_PIN, MIN_INC_BB_TYPE);

	// Minutes decrement
	PushButton MinuteDecButton;
	PushButton_Init(&MinuteDecButton, MIN_DEC_BB_PORT, MIN_DEC_BB_PIN, MIN_DEC_BB_TYPE);

	// Seconds increment
	PushButton SecondIncButton;
	PushButton_Init(&SecondIncButton, SEC_INC_BB_PORT, SEC_INC_BB_PIN, SEC_INC_BB_TYPE);

	// Seconds decrement
	PushButton SecondDecButton;
	PushButton_Init(&SecondDecButton, SEC_DEC_BB_PORT, SEC_DEC_BB_PIN, SEC_DEC_BB_TYPE);

	// Buzzer
	Buzzer myBuzzer;
	Buzzer_Init(&myBuzzer, BUZZER_PORT, BUZZER_PIN);

	// Count up LED
	Led CountUP;
	Led_Init(&CountUP, COUNT_UP_LED_PORT, COUNT_UP_LED_PIN, COUNT_UP_LED_TYPE);

	// Count down LED
	Led CountDOWN;
	Led_Init(&CountDOWN, COUNT_DOWN_LED_PORT, COUNT_DOWN_LED_PIN, COUNT_DOWN_LED_TYPE);

	//Multiple/Multiplexed SevenSegment
	for (int i = 0; i<NUM_SEVEN_SEGMENTS; i++)
	{
		SevenSegment_Init(&g_Mult_SevenSegment[i],SEVEN_SEGMENT_DATA_PORT, SEVEN_SEGMENT_DATA_PINS);
	}
	// external interrupts 0,1,2 initializations
	INT0_Init(FALLING_EDGE);
	INT1_Init(RISING_EDGE);
	INT2_Init(FALLING_EDGE);

	// timer1 initialization to count 1 second
	Timer1_CTC_Init(COMPARE_MATCH_FOR_1SEC, PRESCALAR_1024);

	while(1)
	{
		// 1. put the visual input first
		SevenSegmentUpdate();
		UpdateCountLEDs(&CountUP, &CountDOWN);

	    // 2. Handle Mode Toggle
	    if (ReadButton(&ModeButton) == PRESSED)
	    {
	    	ToggleStopWatchMode;
	        while(ReadButton(&ModeButton) == PRESSED)
	        {
	    		SevenSegmentUpdate();
	    		UpdateCountLEDs(&CountUP, &CountDOWN);
	        }
	    }

	    // 3. Handle Time Adjustment Buttons
	    // 3.1 Hours Increment
	    if (ReadButton(&HourIncButton) == PRESSED)
	    {
	        IncHour();
	        while(ReadButton(&HourIncButton) == PRESSED)
	        {
	    		SevenSegmentUpdate();
	    		UpdateCountLEDs(&CountUP, &CountDOWN);
	        }
	    }

	    // 3.2 Hours Decrement
	    if (ReadButton(&HourDecButton) == PRESSED)
	    {
	        DecHour();
	        while(ReadButton(&HourDecButton) == PRESSED)
	        {
	    		SevenSegmentUpdate();
	    		UpdateCountLEDs(&CountUP, &CountDOWN);
	        }
	    }

	    // 3.3 Minutes Increment
	    if (ReadButton(&MinuteIncButton) == PRESSED)
	    {
	        IncMin();
	        while(ReadButton(&MinuteIncButton) == PRESSED)
	        {
	    		SevenSegmentUpdate();
	    		UpdateCountLEDs(&CountUP, &CountDOWN);
	        }
	    }

	    // 3.4 Minutes Decrement
	    if (ReadButton(&MinuteDecButton) == PRESSED)
	    {
	        DecMin();
	        while(ReadButton(&MinuteDecButton) == PRESSED)
	        {
	    		SevenSegmentUpdate();
	    		UpdateCountLEDs(&CountUP, &CountDOWN);
	        }
	    }

	    // 3.5 Seconds Increment
	    if (ReadButton(&SecondIncButton) == PRESSED)
	    {
	        IncSec();
	        while(ReadButton(&SecondIncButton) == PRESSED)
	        {
	    		SevenSegmentUpdate();
	    		UpdateCountLEDs(&CountUP, &CountDOWN);
	        }
	    }

	    // 3.6 Seconds Decrement
	    if (ReadButton(&SecondDecButton) == PRESSED)
	    {
	        DecSec();
	        while(ReadButton(&SecondDecButton) == PRESSED)
	        {
	    		SevenSegmentUpdate();
	    		UpdateCountLEDs(&CountUP, &CountDOWN);
	        }
	    }

	    // 4. Handle Buzzer (e.g., when count-down reaches 00:00:00)
	    if (g_mode == DECREMENTAL_MODE &&
	    		g_SevenSeg_time.Hour == 0 &&
				g_SevenSeg_time.Min == 0 &&
				g_SevenSeg_time.Sec == 0)
	    {
	        BuzzerOn(&myBuzzer);
	    }
	    else
	    {
	    	BuzzerOff(&myBuzzer);
	    }
	}
}
