#include "GPIO.h"
#include "System.h"
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

int main(void)
{
    System test;
    test.init(40000000);

    GPIO inputValue;
    inputValue.init(&test, GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_DIR_MODE_IN, true);
    inputValue.setPullup(true);

    GPIO outputValue;
    outputValue.init(&test, GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_DIR_MODE_OUT,
                     false);

    uint32_t counter = 1;

    /*
     *  With every button push the state of the LED is supposed to change
     *  The counter variable symbolizes the state of the LED
     *  Every time the button is pushed the counter goes up, remembering the previous state
     */
    while (1)
    {
        if (inputValue.read() == false)
        {
            test.delayUS(50000);
            while (inputValue.read() == false)

                if (counter >= 3)
                {
                    counter = 1;
                }

            switch (counter)
            {
            case 1:

                outputValue.write(true);
                break;

            case 2:
                outputValue.write(false);
                break;
            }

            counter++;

            test.delayUS(50000);

        }

    }
}
