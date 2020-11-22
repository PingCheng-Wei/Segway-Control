#include <stdbool.h>
#include <stdint.h>
#include "System.h"
#include "GPIO.h"
#include "ADC.h"
#include "utils/ustdlib.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/debug.h"
#include "driverlib/hibernate.h"

int main(void)
{
    System test;
    test.init(40000000);

    // Enabling and initializing all needed GPIO and ADC Objects for the pins

    GPIO inputValue_1;
    inputValue_1.init(&test, GPIO_PORTE_BASE, GPIO_PIN_1, GPIO_DIR_MODE_IN,
                      true);
    inputValue_1.setPullup(true);

    ADC Input_1;
    Input_1.init(&test, ADC0_BASE, 0, ADC_CTL_CH2);
    Input_1.setHWAveraging(64);

    GPIO inputValue_R;
    inputValue_R.init(&test, GPIO_PORTE_BASE, GPIO_PIN_2, GPIO_DIR_MODE_IN,
                      true);
    inputValue_R.setPullup(true);

    ADC Input_R;
    Input_R.init(&test, ADC0_BASE, 0, ADC_CTL_CH1);
    Input_R.setHWAveraging(64);

    GPIO redLED;
    redLED.init(&test, GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_DIR_MODE_OUT, false);

    GPIO greenLED;
    greenLED.init(&test, GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_DIR_MODE_OUT, false);

    // Read the value of the voltage in both pins and compare both voltages repeatedly
    // if the input voltage is higher than the reference, the led turns green
    while (1)
    {
        float Input_Volt = Input_1.readVolt();

        float Input_Reference_Volt = Input_R.readVolt();

        if (Input_Volt > Input_Reference_Volt)
        {
            redLED.write(false);
            greenLED.write(true);

        }
        else
        {
            redLED.write(true);
            greenLED.write(false);

        }

        test.delayUS(50000);
    }
}
