/*
 * GPIO.h
 *
 */

//The RCGCGPIO register provides software the capability
//to enable and disable GPIO modules in Run mode

#define GPIO_PORT_ALLE_BASE 0x400FE000
#define OFFSET 0x608

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include <System.h>
#ifndef GPIO_H_
#define GPIO_H_

class GPIO
{

public:
    GPIO();
    virtual ~GPIO();
    void init(System *sys, uint32_t portBase, uint32_t pin, uint32_t dir,
              bool pullup = false);
    bool read();
    void write(bool state);
    uint32_t getCurrent();
    void setCurrent(uint32_t current);
    void setPullup(bool pullup);
    void setPulldown(bool pulldown);

private:
    uint32_t gpioPortBase;
    uint32_t gpioPin;
    uint32_t gpioDir;
    uint32_t gpioCurrent;
    uint32_t gpioPinType;
    const uint32_t gpioStrengthArray[7] = { 0, GPIO_STRENGTH_2MA,
                                            GPIO_STRENGTH_4MA,
                                            GPIO_STRENGTH_6MA,
                                            GPIO_STRENGTH_8MA,
                                            GPIO_STRENGTH_10MA,
                                            GPIO_STRENGTH_12MA };
};

#endif /* GPIO_H_ */
