/*
 * PWM.cpp
 *
 */

#include <PWM.h>

PWM::PWM()
{
    // TODO Auto-generated constructor stub

}

PWM::~PWM()
{
    // TODO Auto-generated destructor stub
}
void PWM::init(System *sys, uint32_t portBase, uint32_t pin1, uint32_t pin2,
               bool invert, uint32_t freq)
{
    GPIOBase = portBase;
    pwmPin1 = pin1;
    pwmPin2 = pin2;
    pwmFreq = freq;
    pwmInvert = invert;
    sys = sys;

    /*
     * The generators and modules for the pins can be found in the datasheet.
     * Table 20.1 , S.1233
     *
     * SysCtlPeripheralEnable enables the right GPIO Peripheral and PWM Module
     *
     * GPIOPinConfigure matches the pins with the right PWM output signal
     */

    switch ((GPIOBase | pwmPin1 | pwmPin2))
    {
    case ((GPIO_PORTB_BASE | GPIO_PIN_6 | GPIO_PIN_7)):
        pwmGen = PWM_GEN_0;
        pwmBase = PWM0_BASE;
        pwmOutPin1 = PWM_OUT_0;
        pwmOutPin2 = PWM_OUT_1;
        pwmOutBitPin1 = PWM_OUT_0_BIT;
        pwmOutBitPin2 = PWM_OUT_1_BIT;

        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);

        GPIOPinConfigure(GPIO_PB6_M0PWM0);
        GPIOPinConfigure(GPIO_PB7_M0PWM1);
        break;

    case ((GPIO_PORTD_BASE | GPIO_PIN_0 | GPIO_PIN_1)):
        pwmGen = PWM_GEN_0;
        pwmBase = PWM1_BASE;
        pwmOutPin1 = PWM_OUT_0;
        pwmOutPin2 = PWM_OUT_1;
        pwmOutBitPin1 = PWM_OUT_0_BIT;
        pwmOutBitPin2 = PWM_OUT_1_BIT;

        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
        GPIOPinConfigure(GPIO_PD0_M1PWM0);
        GPIOPinConfigure(GPIO_PD1_M1PWM1);
        break;

    case ((GPIO_PORTB_BASE | GPIO_PIN_4 | GPIO_PIN_5)):
        pwmGen = PWM_GEN_1;
        pwmBase = PWM0_BASE;
        pwmOutPin1 = PWM_OUT_2;
        pwmOutPin2 = PWM_OUT_3;
        pwmOutBitPin1 = PWM_OUT_4_BIT;
        pwmOutBitPin2 = PWM_OUT_5_BIT;

        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
        GPIOPinConfigure(GPIO_PB4_M0PWM2);
        GPIOPinConfigure(GPIO_PB5_M0PWM3);
        break;

    case ((GPIO_PORTA_BASE | GPIO_PIN_6 | GPIO_PIN_7)):
        pwmGen = PWM_GEN_1;
        pwmBase = PWM1_BASE;
        pwmOutPin1 = PWM_OUT_2;
        pwmOutPin2 = PWM_OUT_3;
        pwmOutBitPin1 = PWM_OUT_2_BIT;
        pwmOutBitPin2 = PWM_OUT_3_BIT;

        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
        GPIOPinConfigure(GPIO_PA6_M1PWM2);
        GPIOPinConfigure(GPIO_PA7_M1PWM3);
        break;

    case ((GPIO_PORTE_BASE | GPIO_PIN_4 | GPIO_PIN_5)):
        pwmGen = PWM_GEN_2;
        pwmBase = PWM0_BASE;
        pwmOutPin1 = PWM_OUT_4;
        pwmOutPin2 = PWM_OUT_5;
        pwmOutBitPin1 = PWM_OUT_4_BIT;
        pwmOutBitPin2 = PWM_OUT_5_BIT;

        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
        GPIOPinConfigure(GPIO_PE4_M0PWM4);
        GPIOPinConfigure(GPIO_PE5_M0PWM5);
        break;

    case ((GPIO_PORTF_BASE | GPIO_PIN_0 | GPIO_PIN_1)):
        pwmGen = PWM_GEN_2;
        pwmBase = PWM1_BASE;
        pwmOutPin1 = PWM_OUT_4;
        pwmOutPin2 = PWM_OUT_5;
        pwmOutBitPin1 = PWM_OUT_4_BIT;
        pwmOutBitPin2 = PWM_OUT_5_BIT;

        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
        GPIOPinConfigure(GPIO_PF0_M1PWM4);
        GPIOPinConfigure(GPIO_PF1_M1PWM5);
        //PF0 is locked with GPIO functionality. It needs to be unlocked with the GPIOLOCK register
        HWREG(GPIO_PORTF_BASE+GPIO_O_LOCK) = GPIO_LOCK_KEY;
        HWREG(GPIO_PORTF_BASE+GPIO_O_CR) |= 0x00;
        HWREG(GPIO_PORTF_BASE+GPIO_O_CR) |= 0x01;
        break;

    case ((GPIO_PORTC_BASE | GPIO_PIN_4 | GPIO_PIN_5)):
        pwmGen = PWM_GEN_3;
        pwmBase = PWM0_BASE;
        pwmOutPin1 = PWM_OUT_6;
        pwmOutPin2 = PWM_OUT_7;
        pwmOutBitPin1 = PWM_OUT_6_BIT;
        pwmOutBitPin2 = PWM_OUT_7_BIT;

        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
        GPIOPinConfigure(GPIO_PC4_M0PWM6);
        GPIOPinConfigure(GPIO_PC5_M0PWM7);
        break;

    case ((GPIO_PORTF_BASE | GPIO_PIN_2 | GPIO_PIN_3)):
        pwmGen = PWM_GEN_3;
        pwmBase = PWM1_BASE;
        pwmOutPin1 = PWM_OUT_6;
        pwmOutPin2 = PWM_OUT_7;
        pwmOutBitPin1 = PWM_OUT_6_BIT;
        pwmOutBitPin2 = PWM_OUT_7_BIT;

        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
        GPIOPinConfigure(GPIO_PF2_M1PWM6);
        GPIOPinConfigure(GPIO_PF3_M1PWM7);
        break;
    default:
        break;
    };

    GPIOPinTypePWM(GPIOBase, pwmPin1);
    GPIOPinTypePWM(GPIOBase, pwmPin2);

    // The generator needs to be configured
    // MODE_UP_DOWN is better for motor control as it results in a symmetrical and in phase

    PWMGenConfigure(pwmBase, pwmGen,
    PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_GEN_SYNC_LOCAL);

    setFreq(pwmFreq);

    PWMGenEnable(pwmBase, pwmGen);
    //Inverts the signal, standard is non-inverted Output
    PWMOutputInvert(pwmBase, pwmOutBitPin1 | pwmOutBitPin2, pwmInvert);

    //There is only supposed to be an output after setDuty() is called
    PWMOutputState(pwmBase, pwmOutBitPin1 | pwmOutBitPin2, false);

}
;

void PWM::setFreq(uint32_t freq)
{
    /*
     * Period is calculated by dividing the systemclockfrequency with PWMDiv.
     * This new frequency is divided with the pwm Frequency to get the clock ticks of one period
     * It is assumed that the system runs with a PWMDiv of 16
     */
    pwmFreq = freq;
    pwmPeriod = (SysCtlClockGet()/16)/ pwmFreq;
    PWMGenPeriodSet(pwmBase, pwmGen, pwmPeriod);

}
;

void PWM::setDuty(float duty)
{

    pwmDuty = duty;
    sys->enableFPU();

    if (fabs(pwmDuty) > 1)
    // Limit pwmDuty between -100% and 100%
    {
        pwmDuty = 0;
    }

    if (pwmOutPin2 < pwmOutPin1)
        // Pin1 and Pin2 are swapped, if Pin2 is smaller than Pin1
        // This way you can assume that Pin1 is always the smaller Pin
    {
        uint32_t PinZwischenspeicher = pwmOutPin2;
        pwmOutPin2 = pwmOutPin1;
        pwmOutPin1 = PinZwischenspeicher;
    }

    //If duty is positive the Signal is applied to Pin1, a negative duty results in the signal being applied to Pin2
    // values between -0.1 and 0.1 are assumed to 0 to avoid jumps between directions around 0
    if (pwmDuty > 0.1)
    {
        PWMPulseWidthSet(pwmBase, pwmOutPin1, pwmDuty * pwmPeriod);
        PWMPulseWidthSet(pwmBase, pwmOutPin2, 0);
    }
    else if (pwmDuty < -0.1)
    {
        PWMPulseWidthSet(pwmBase, pwmOutPin1, 0);
        PWMPulseWidthSet(pwmBase, pwmOutPin2, fabs(pwmDuty) * pwmPeriod);
    }
    else
    //For every other value(0 or not valid) both Pins are off
    {
        PWMPulseWidthSet(pwmBase, pwmOutPin1, 0);
        PWMPulseWidthSet(pwmBase, pwmOutPin2, 0);
    };

    //Enabling the Output after setDuty is called
    PWMOutputState(pwmBase, pwmOutBitPin2 | pwmOutBitPin1, true);

}
;

