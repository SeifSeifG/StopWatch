#include "Timers.h"
#include "Led.h"


static void SetPreScalar(Timer timer,  TimerSetting preScalar);
static TimerSetting Timer0_Pre;
static TimerSetting Timer1_Pre;
static TimerSetting Timer2_Pre;


void Timer0_Normal_Init(TimerSetting preScalar, TimerTechnique technique)
{
	// store pre-scalar for resume function
	Timer0_Pre = preScalar;

	//Set Timer initial value to 0
	TCNT0 = 0;

	// specify timer mode
	CLEAR(TCCR0, WGM00);
	CLEAR(TCCR0, WGM01);

	SetPreScalar(Timer0, preScalar);

	// for Non PWM mode FOC0=1
	SET(TCCR0, FOC0);

	if (technique == INTERRUPT)
	{
		SET(TIMSK, TOIE0); // Enable Timer0 Overflow Interrupt
		sei();
	}
}
void Timer1_Normal_Init(TimerSetting preScalar, TimerTechnique technique)
{
	// store pre-scalar for resume function
	Timer1_Pre = preScalar;

    // Set Timer initial value to 0
    TCNT1 = 0;

    // Specify timer mode (Normal mode)
    CLEAR(TCCR1A, WGM10);
    CLEAR(TCCR1A, WGM11);
    CLEAR(TCCR1B, WGM12);
    CLEAR(TCCR1B, WGM13);

    SetPreScalar(Timer1, preScalar);

    // For Non-PWM mode, force compare
    SET(TCCR1A, FOC1A);
    SET(TCCR1A, FOC1B);

    if (technique == INTERRUPT)
    {
        SET(TIMSK, TOIE1); // Enable Timer1 Overflow Interrupt
		sei();
    }
}

void Timer2_Normal_Init(TimerSetting preScalar, TimerTechnique technique)
{
	// store pre-scalar for resume function
	Timer2_Pre = preScalar;

    // Set Timer initial value to 0
    TCNT2 = 0;

    // Specify timer mode (Normal mode)
    CLEAR(TCCR2, WGM20);
    CLEAR(TCCR2, WGM21);

    SetPreScalar(Timer2, preScalar);

    // For Non-PWM mode, force compare
    SET(TCCR2, FOC2);

    if (technique == INTERRUPT)
    {
        SET(TIMSK, TOIE2); // Enable Timer2 Overflow Interrupt
		sei();
    }
}


void Timer0_CTC_Init(uint8 compareVal, TimerSetting preScalar)
{
    cli();
	// store pre-scalar for resume function
	Timer0_Pre = preScalar;

	// Set Timer initial value to 0
    TCNT0 = 0;

    OCR0 = compareVal; // Set Compare Value

    CLEAR(TCCR0, WGM00);
    SET(TCCR0, WGM01);

    SetPreScalar(Timer0, preScalar);

    SET(TCCR0, FOC0);

    SET(TIMSK, OCIE0); // Enable Timer0 Compare Interrupt
    sei();
}

void Timer1_CTC_Init(uint16 compareVal, TimerSetting preScalar)
{

    cli();                      // Disable interrupts
	Timer1_Pre = preScalar;		// store pre-scalar for resume function
    TCNT1 = 0;                  // Reset Timer1 counter

    OCR1A = compareVal;         // Set compare value for Channel A

    // Configure CTC mode (WGM13:0 = 0100)
    CLEAR(TCCR1A, WGM10);
    CLEAR(TCCR1A, WGM11);
    SET(TCCR1B, WGM12);
    CLEAR(TCCR1B, WGM13);

    SetPreScalar(Timer1, preScalar);

    // Force compare (non-PWM mode)
    SET(TCCR1A, FOC1A);
    SET(TCCR1A, FOC1B);

    SET(TIMSK, OCIE1A);     	// Enable Timer1 Compare A Match Interrupt

    sei();                      // Enable interrupts
}

void Timer2_CTC_Init(uint8 compareVal, TimerSetting preScalar)
{
    cli();                      // Disable interrupts
	Timer2_Pre = preScalar;		// store pre-scalar for resume function
    TCNT2 = 0;                  // Reset Timer2 counter

    OCR2 = compareVal;          // Set compare value

    // Configure CTC mode (WGM21:20 = 01)
    CLEAR(TCCR2, WGM20);
    SET(TCCR2, WGM21);

    SetPreScalar(Timer2, preScalar);

    // Force compare (non-PWM mode)
    SET(TCCR2, FOC2);

    SET(TIMSK, OCIE2);      // Enable Timer2 Compare Match Interrupt

    sei();                      // Enable interrupts
}

void Timer0_OFF()
{
    // Stop Timer0 by clearing pre-scaler bits (CS02:00 = 0)
    CLEAR(TCCR0, CS00);
    CLEAR(TCCR0, CS01);
    CLEAR(TCCR0, CS02);
}

void Timer0_ON()
{
    SetPreScalar(Timer0, Timer0_Pre);
}

void Timer1_OFF()
{
    // Stop Timer1 by clearing pre-scaler bits (CS12:10 = 0)
    CLEAR(TCCR1B, CS10);
    CLEAR(TCCR1B, CS11);
    CLEAR(TCCR1B, CS12);
}

void Timer1_ON()
{
    SetPreScalar(Timer1, Timer1_Pre);
}

void Timer2_OFF()
{
    // Stop Timer2 by clearing pre-scaler bits (CS22:20 = 0)
    CLEAR(TCCR2, CS20);
    CLEAR(TCCR2, CS21);
    CLEAR(TCCR2, CS22);
}

void Timer2_ON()
{
    SetPreScalar(Timer2, Timer2_Pre);
}

static void SetPreScalar(Timer timer,  TimerSetting preScalar)
{
    switch(timer)
    {
        case Timer0:
            switch (preScalar)
            {
                case NO_PRESCALAR:      CLEAR(TCCR0,CS02); CLEAR(TCCR0,CS01); SET(TCCR0,CS00); break;
                case PRESCALAR_8:       CLEAR(TCCR0,CS02); SET(TCCR0,CS01); CLEAR(TCCR0,CS00); break;
                case PRESCALAR_64:      CLEAR(TCCR0,CS02); SET(TCCR0,CS01); SET(TCCR0,CS00); break;
                case PRESCALAR_256:     SET(TCCR0,CS02); CLEAR(TCCR0,CS01); CLEAR(TCCR0,CS00); break;
                case PRESCALAR_1024:    SET(TCCR0,CS02); CLEAR(TCCR0,CS01); SET(TCCR0,CS00); break;
                case EXT_FALLING_EDGE:  SET(TCCR0,CS02); SET(TCCR0,CS01); CLEAR(TCCR0,CS00); break;
                case EXT_RISING_EDGE:   SET(TCCR0,CS02); SET(TCCR0,CS01); SET(TCCR0,CS00); break;
            }
            break;

        case Timer1:
            switch (preScalar)
            {
                case NO_PRESCALAR:      CLEAR(TCCR1B,CS12); CLEAR(TCCR1B,CS11); SET(TCCR1B,CS10); break;
                case PRESCALAR_8:       CLEAR(TCCR1B,CS12); SET(TCCR1B,CS11); CLEAR(TCCR1B,CS10); break;
                case PRESCALAR_64:      CLEAR(TCCR1B,CS12); SET(TCCR1B,CS11); SET(TCCR1B,CS10); break;
                case PRESCALAR_256:     SET(TCCR1B,CS12); CLEAR(TCCR1B,CS11); CLEAR(TCCR1B,CS10); break;
                case PRESCALAR_1024:    SET(TCCR1B,CS12); CLEAR(TCCR1B,CS11); SET(TCCR1B,CS10); break;
                case EXT_FALLING_EDGE:  SET(TCCR1B,CS12); SET(TCCR1B,CS11); CLEAR(TCCR1B,CS10); break;
                case EXT_RISING_EDGE:   SET(TCCR1B,CS12); SET(TCCR1B,CS11); SET(TCCR1B,CS10); break;
            }
            break;

        case Timer2:
            switch (preScalar)
            {
                case NO_PRESCALAR:      CLEAR(TCCR2,CS22); CLEAR(TCCR2,CS21); SET(TCCR2,CS20); break;
                case PRESCALAR_8:       CLEAR(TCCR2,CS22); SET(TCCR2,CS21); CLEAR(TCCR2,CS20); break;
                case PRESCALAR_64:      CLEAR(TCCR2,CS22); SET(TCCR2,CS21); SET(TCCR2,CS20); break;
                case PRESCALAR_256:     SET(TCCR2,CS22); CLEAR(TCCR2,CS21); CLEAR(TCCR2,CS20); break;
                case PRESCALAR_1024:    SET(TCCR2,CS22); CLEAR(TCCR2,CS21); SET(TCCR2,CS20); break;
                case EXT_FALLING_EDGE:  SET(TCCR2,CS22); SET(TCCR2,CS21); CLEAR(TCCR2,CS20); break;
                case EXT_RISING_EDGE:   SET(TCCR2,CS22); SET(TCCR2,CS21); SET(TCCR2,CS20); break;
            }
            break;
    }
}
