/*
 * Timer.h
 *
 */

// Control the clocking for the timer modules according to Register 59
// of the Tiva C Series Data Sheet
#define TIMER_BASE 0x400FE000
#define TIMER_OFFSET 0x604

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

#ifndef TIMER_H_
#define TIMER_H_

class Timer
{
public:
    Timer();
    virtual ~Timer();
    void init(System *sys, uint32_t base, void (*ISR)(), uint32_t freq);
    void start();
    void stop();
    uint32_t getFreq();
    uint32_t getPeriodUS();
    void setFreq(uint32_t freq);
    void setPeriodUS(uint32_t period);
    void clearInterruptFlag();

private:
    uint32_t timerBase;
    uint32_t timerFrequency;
};

#endif /* TIMER_H_ */
