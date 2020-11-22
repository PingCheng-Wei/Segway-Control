/*
 * GPIO.cpp
 *
 */

#include <GPIO.h>

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

GPIO::GPIO()
{
    // TODO Auto-generated constructor stub

}

GPIO::~GPIO()
{
    // TODO Auto-generated destructor stub
}

void GPIO::init(System *sys, uint32_t portBase, uint32_t pin, uint32_t dir,
                bool pullup)
{
    // Enabling the right port in the RCGCGPIO register
    switch (portBase)
    {
    case GPIO_PORTA_BASE:
        HWREG (GPIO_PORT_ALLE_BASE+OFFSET) |= 0b000001;
        break;

    case GPIO_PORTB_BASE:
        HWREG (GPIO_PORT_ALLE_BASE+OFFSET) |= 0b000010;
        break;

    case GPIO_PORTC_BASE:
        HWREG (GPIO_PORT_ALLE_BASE+OFFSET) |= 0b000100;
        break;

    case GPIO_PORTD_BASE:
        HWREG (GPIO_PORT_ALLE_BASE+OFFSET) |= 0b001000;
        break;

    case GPIO_PORTE_BASE:
        HWREG (GPIO_PORT_ALLE_BASE+OFFSET) |= 0b010000;
        break;

    case GPIO_PORTF_BASE:
        HWREG (GPIO_PORT_ALLE_BASE+OFFSET) |= 0b100000;
        break;
    }

    gpioPortBase = portBase;
    gpioPin = pin;
    gpioCurrent = GPIO_STRENGTH_4MA;
    gpioDir = dir;

    // Configure the pin as input or output
    if (gpioDir == GPIO_DIR_MODE_IN)
    {
        GPIOPinTypeGPIOInput(gpioPortBase, gpioPin);
    }
    else
    {
        GPIOPinTypeGPIOOutput(gpioPortBase, gpioPin);
    }

    setPullup(pullup);

}

bool GPIO::read()
{
    return GPIOPinRead(gpioPortBase, gpioPin);
}

void GPIO::write(bool state)
{
    // For the GPIOPinWrite function the gpioPin variable has the right Bit-ID
    if (state == false)
    {
        GPIOPinWrite(gpioPortBase, gpioPin, 0x00);
    }
    else
    {
        GPIOPinWrite(gpioPortBase, gpioPin, gpioPin);
    }
}

uint32_t GPIO::getCurrent()
{
    // Reading out of the previously created array
    if (gpioCurrent == GPIO_STRENGTH_2MA)
        return 2;
    else if (gpioCurrent == GPIO_STRENGTH_4MA)
        return 4;
    else if (gpioCurrent == GPIO_STRENGTH_6MA)
        return 6;
    else if (gpioCurrent == GPIO_STRENGTH_8MA)
        return 8;
    else if (gpioCurrent == GPIO_STRENGTH_10MA)
        return 10;
    else if (gpioCurrent == GPIO_STRENGTH_12MA)
        return 12;
    else
        return 0;
}

void GPIO::setCurrent(uint32_t current)
{
    // The result of the division with 2 mA corresponds to the number in the array because the first value is 0
    gpioCurrent = gpioStrengthArray[current / 2];

    GPIOPadConfigSet(gpioPortBase, gpioPin, gpioCurrent, gpioPinType);
}

void GPIO::setPullup(bool pullup)
{
    if (pullup)
    {
        gpioPinType = GPIO_PIN_TYPE_STD_WPU;
    }
    else
    {
        gpioPinType = GPIO_PIN_TYPE_STD;
    }
    GPIOPadConfigSet(gpioPortBase, gpioPin, gpioCurrent, gpioPinType);

}

void GPIO::setPulldown(bool pulldown)
{
    if (pulldown)
    {
        gpioPinType = GPIO_PIN_TYPE_STD_WPD;
        GPIOPadConfigSet(gpioPortBase, gpioPin, gpioCurrent, gpioPinType);
    }
    else
        gpioPinType = GPIO_PIN_TYPE_STD;
    GPIOPadConfigSet(gpioPortBase, gpioPin, gpioCurrent, gpioPinType);
}
