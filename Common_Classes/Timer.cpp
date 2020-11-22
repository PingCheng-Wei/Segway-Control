/*
 * Timer.cpp
 *
 */

#include <Timer.h>

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include <System.h>

#include "inc/tm4c123gh6pm.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"

Timer::Timer()
{
    // TODO Auto-generated constructor stub

}

Timer::~Timer()
{
    // TODO Auto-generated destructor stub
}

void Timer::init(System *sys, uint32_t base, void (*ISR)(), uint32_t freq)
{

    timerFrequency = freq;
    timerBase = base;

    // Enabling the right timer base in the RCGCGPIO register
    switch (base)
    {
    case TIMER0_BASE:
        HWREG (TIMER_BASE+TIMER_OFFSET) |= 0b000001;
        break;

    case TIMER1_BASE:
        HWREG (TIMER_BASE+TIMER_OFFSET) |= 0b000010;
        break;

    case TIMER2_BASE:
        HWREG (TIMER_BASE+TIMER_OFFSET) |= 0b000100;
        break;

    case TIMER3_BASE:
        HWREG (TIMER_BASE+TIMER_OFFSET) |= 0b001000;
        break;

    case TIMER4_BASE:
        HWREG (TIMER_BASE+TIMER_OFFSET) |= 0b010000;
        break;

    case TIMER5_BASE:
        HWREG (TIMER_BASE+TIMER_OFFSET) |= 0b100000;
        break;
    }

    // Configure the timer as a full-width timer
    TimerConfigure(timerBase, TIMER_CFG_PERIODIC);

    // Enable the interrupts, workshop page 99
    TimerIntEnable(timerBase, TIMER_TIMA_TIMEOUT);
    TimerIntRegister(timerBase, TIMER_A, ISR);
    IntMasterEnable();
    IntEnable(INT_TIMER0A);

    // Initialize the timer with a frequency that was inputed at start
    setFreq(timerFrequency);

}

void Timer::start()
{
    TimerEnable(timerBase, TIMER_A);
}

void Timer::stop()
{
    // Disable and the timer and clear the interrupt flag
    TimerDisable(timerBase, TIMER_A);
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
}

uint32_t Timer::getFreq()
{
    // Return the frequency directly from the variable
    return timerFrequency;
}

uint32_t Timer::getPeriodUS()
{
    /*
     * Return the period by the following calculations 1/frequency
     * the answer was multiplied by 1000000 to convert the period
     * from seconds to microseconds
     */
    return 1000000 / timerFrequency;
}

void Timer::setFreq(uint32_t freq)
{
    // Stop the timer with the Timer::stop function if frequency = 0
    if (freq == 0)
    {
        stop();
    }
    else
    {
        /*
         *  Generate the interrupt with desired period. (SysCtlClockGet() / freq)-1
         *  was used to calculate the desired delay, a value of 1 is deducted as the
         *  interrupt starts at zero count. [referred to workshop page 99]
         */
        TimerLoadSet(timerBase, TIMER_A, (SysCtlClockGet() / freq)-1);
        timerFrequency = freq;
    }
}

void Timer::setPeriodUS(uint32_t period)
{
    // Stop the timer with the stop function if period = 0
    if (period == 0)
    {
        stop();
        timerFrequency = 0;
    }
    // A cycle was deducted in the TimerLoadSet function as one cycle has already passed
    else
    {
        timerFrequency = 1000000 / period;
        TimerLoadSet(timerBase, TIMER_A,
                     (SysCtlClockGet() / timerFrequency) - 1);
    }
}

void Timer::clearInterruptFlag()
{
    TimerIntClear(timerBase, TIMER_TIMA_TIMEOUT);
}
