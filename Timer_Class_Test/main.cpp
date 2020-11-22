#include <stdbool.h>
#include <stdint.h>
#include "System.h"
#include "GPIO.h"
#include "Timer.h"

System sys;
Timer timer1;
GPIO ledRed;
GPIO ledBlue;
int timerCounter = 0;

void ISR()
{
    //Clear interrupt flag
    timer1.clearInterruptFlag();

    /*
     * The timerCounter is increased by 1 every time the ISR is called.
     * As the ISR must be ran 2 times to turn the LED off and on, the timer
     * must be ran with e.g 2 Hz if the LED is to blink at a rate of 1Hz.
     * For an interval of 10 seconds the ISR must be ran for a total amount of
     * 60 times, hence when timerCounter is 61 the red LED will be turned off
     * and the blue LED will be initialized and turned on.
     */
    if (timerCounter < 60)
    {
        ledBlue.write(false);
        ledRed.write(!ledRed.read());
        ledRed.init(&sys, GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_DIR_MODE_OUT,
                    false);
    }

    if (timerCounter >= 60)
    {
        ledRed.write(false);
        ledBlue.write(!ledBlue.read());
        ledBlue.init(&sys, GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_DIR_MODE_OUT,
                     false);
    }


    /*
     * The timer is ran at a Frequency double to that of the wished Frequency,
     * hence the 2, 4, 6, 8, 10Hz as opposed to 1, 2, 3, 4, 5 Hz wished.
     * The frequency is set every time the timerCounter has reached the wished number.
     * As the frequency is changed every 2 second, the frequency will be increased
     * with timerCounter = timerCounter + Frequency * 2.
     */

    switch (timerCounter)
    {
    case 4:
        timer1.setFreq(4);
        break;

    case 12:
        timer1.setFreq(6);
        break;

    case 24:
        timer1.setFreq(8);
        break;

    case 40:
        timer1.setFreq(10);
        break;
    // When timerCounter is 60 the blue LED will be initialized.
    // The frequency of the blue LED starts to decrease here
    case 80:
        timer1.setFreq(8);
        break;

    case 96:
        timer1.setFreq(6);
        break;

    case 108:
        timer1.setFreq(4);
        break;

    case 116:
        timer1.setFreq(2);
        break;
    }

    // timerCounter increases every time the ISR is ran as mentioned
    // at the start.
    timerCounter++;

    if (timerCounter >= 120)
    {
        // Set timerCounter back to 0 to repeat the process again as
        // ISR has been ran for 120 times.
        timerCounter = 0;

    }

}

int main(void)
{
    //initialize the clock and set the CPU clock frequency
    sys.init(40000000);

    /*
     * Using the GPIO init function to set the red LED as an output. Initialize
     * the timer with a frequency of 1 Hz and a pointer towards ISR and start
     * the timer.
     */

    ledRed.init(&sys, GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_DIR_MODE_OUT, false);
    timer1.init(&sys, TIMER0_BASE, &ISR, 2);
    timer1.start();

    while (1)
    {

    }

}

