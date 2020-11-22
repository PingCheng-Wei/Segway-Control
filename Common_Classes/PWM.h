#ifndef PWM_H_
#define PWM_H_
#include <System.h>
#include <driverlib/pwm.h>
#include "driverlib/fpu.h"
#include <math.h>
#include <driverlib/sysctl.h>
#include <driverlib/gpio.h>
#include <driverlib/sysctl.h>
#include <driverlib/gpio.h>
#include <uartstdio.h>



class PWM
{
public:
    PWM();
    virtual ~PWM();
    void init(System *sys, uint32_t portBase, uint32_t pin1,uint32_t pin2, bool invert = 0, uint32_t freq = 5000);
    void setFreq(uint32_t freq);
    void setDuty(float duty);

private:
    /*
     *  pwmPeriod: Periode des PWM Signals in Clock Ticks
     *  pwmOutPin1, pwmOutPin2: Offset Adresse der PWM Outputs
     *  pwmOutBitPin1, pwmOutBitPin2: Bit IDs der PWM Outputs
     */
    System *sys;
    uint32_t GPIOBase;
    uint32_t pwmBase;
    uint32_t pwmGen;
    uint32_t pwmConfig;
    uint32_t pwmFreq;
    uint32_t pwmPeriod;
    uint32_t pwmPin1, pwmPin2;
    uint32_t pwmOutPin1, pwmOutPin2;
    uint32_t pwmOutBitPin1, pwmOutBitPin2;
    float pwmDuty;
    bool pwmInvert;





};

#endif /* PWM_H_ */

