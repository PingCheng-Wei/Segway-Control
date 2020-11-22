#include <stdbool.h>
#include <stdint.h>
#include "System.h"
#include "GPIO.h"
#include "PWM.h"
#include <System.h>
#include <PWM.h>
#include <GPIO.h>
#include <ADC.h>

int main(void)
{
    System test;
    test.init(40000000);

    PWM MotorLinks;
    MotorLinks.init(&test, GPIO_PORTD_BASE, GPIO_PIN_0, GPIO_PIN_1);

    PWM MotorRechts;
    MotorRechts.init(&test, GPIO_PORTE_BASE, GPIO_PIN_4, GPIO_PIN_5, false,
                     2500);

    GPIO TreiberEnable;
    TreiberEnable.init(&test, GPIO_PORTD_BASE, GPIO_PIN_3, GPIO_DIR_MODE_OUT,
                       false);
    TreiberEnable.write(true);

    while (1)
    {
        // testing different speeds and Directions
        MotorLinks.setDuty(0.7);
        MotorRechts.setDuty(0.7);
        test.delayCycles(80000000);

        MotorLinks.setDuty(0.0);
        MotorRechts.setDuty(0.0);
        test.delayCycles(80000000);

        MotorLinks.setDuty(0.3);
        MotorRechts.setDuty(-0.3);
        test.delayCycles(80000000);

        MotorLinks.setDuty(0.0);
        MotorRechts.setDuty(0.0);
        test.delayCycles(80000000);

    };

}
;
