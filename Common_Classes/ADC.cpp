/*
 * ADC.cpp
 *
 */

#include <ADC.h>
#include <stdint.h>
#include <stdbool.h>
#include <System.h>
#include "utils/ustdlib.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/debug.h"
#include "driverlib/hibernate.h"
#include "driverlib/adc.h"

ADC::ADC()
{
    // TODO Auto-generated constructor stub

}

ADC::~ADC()
{
    // TODO Auto-generated destructor stub
}

void ADC::init(System *sys, uint32_t base, uint32_t sampleSeq,
               uint32_t analogInput)
{
    // Enable the ADC clock using the RCGCADC register , page 352 of the Tivaware Datasheet
    switch (base)
    {
    case ADC0_BASE:
        HWREG (RCGCADC_BASE + OFFSET_ADC) |= 0b01;
        break;

    case ADC1_BASE:
        HWREG (RCGCADC_BASE+OFFSET_ADC) |= 0b10;
        break;
    }

    adcBase = base;
    adcAnalogInput = analogInput;
    adcSampleSeq = sampleSeq;

    // Configure the right Sample Sequencer. Every Sequencer gets a priority that is equivalent to its number
    switch (adcSampleSeq)
    {
    case 0:
        ADCSequenceConfigure(adcBase, adcSampleSeq, ADC_TRIGGER_PROCESSOR, 0);
        break;
    case 1:
        ADCSequenceConfigure(adcBase, adcSampleSeq, ADC_TRIGGER_PROCESSOR, 1);
        break;
    case 2:
        ADCSequenceConfigure(adcBase, adcSampleSeq, ADC_TRIGGER_PROCESSOR, 2);
        break;
    case 3:
        ADCSequenceConfigure(adcBase, adcSampleSeq, ADC_TRIGGER_PROCESSOR, 3);
        break;
    }

    ADCSequenceStepConfigure(adcBase, adcSampleSeq, 0, adcAnalogInput);
    ADCSequenceStepConfigure(adcBase, adcSampleSeq, 1, adcAnalogInput);
    ADCSequenceStepConfigure(adcBase, adcSampleSeq, 2, adcAnalogInput);
    ADCSequenceStepConfigure(adcBase, adcSampleSeq, 3,
                             adcAnalogInput | ADC_CTL_IE | ADC_CTL_END);

    ADCSequenceEnable(adcBase, adcSampleSeq);

    // Enabling the Input Pin as ADC
    switch (analogInput)
    {
    case ADC_CTL_CH0:
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
        GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_3);
        break;
    case ADC_CTL_CH1:
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
        GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_2);
        break;
    case ADC_CTL_CH2:
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
        GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_1);
        break;
    case ADC_CTL_CH3:
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
        GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_0);
        break;
    case ADC_CTL_CH4:
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
        GPIOPinTypeADC(GPIO_PORTD_BASE, GPIO_PIN_3);
        break;
    case ADC_CTL_CH5:
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
        GPIOPinTypeADC(GPIO_PORTD_BASE, GPIO_PIN_2);
        break;
    case ADC_CTL_CH6:
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
        GPIOPinTypeADC(GPIO_PORTD_BASE, GPIO_PIN_1);
        break;
    case ADC_CTL_CH7:
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
        GPIOPinTypeADC(GPIO_PORTD_BASE, GPIO_PIN_0);
        break;
    case ADC_CTL_CH8:
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
        GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_5);
        break;
    case ADC_CTL_CH9:
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
        GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_4);
        break;
    case ADC_CTL_CH10:
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
        GPIOPinTypeADC(GPIO_PORTB_BASE, GPIO_PIN_4);
        break;
    case ADC_CTL_CH11:
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
        GPIOPinTypeADC(GPIO_PORTB_BASE, GPIO_PIN_5);
        break;
    }

}

void ADC::setHWAveraging(uint32_t averaging)
{
    // Oversampling is accomplished by averaging multiple samples from the same analog input
    // Configuring how many samples to use with "averaging"
    switch (averaging)
    {
    case 2:
        ADCHardwareOversampleConfigure(adcBase, 2);
        break;
    case 4:
        ADCHardwareOversampleConfigure(adcBase, 4);
        break;
    case 8:
        ADCHardwareOversampleConfigure(adcBase, 8);
        break;
    case 16:
        ADCHardwareOversampleConfigure(adcBase, 16);
        break;
    case 32:
        ADCHardwareOversampleConfigure(adcBase, 32);
        break;
    case 64:
        ADCHardwareOversampleConfigure(adcBase, 64);
        break;
    }

    // Specifying an oversampling factor of zero disables hardware oversampling
    if (averaging == 0)
    {
        ADCHardwareOversampleConfigure(adcBase, 0);
    }

}

uint32_t ADC::read()
{
    // The following definition will create an array that will be used for storing the data read
    // from the ADC FIFO.

    IntMasterDisable();

    // Make sure that the flag is cleared before writing code that depends on it
    ADCIntClear(adcBase, adcSampleSeq);

    // Trigger the ADC conversion with software
    ADCProcessorTrigger(adcBase, adcSampleSeq);

    // ADCIntStatus returns the interrupt status for the specified sample sequence
    // Waiting for the conversion to complete
    while (!ADCIntStatus(adcBase, adcSampleSeq, false))
    {
    }
    ADCSequenceStepConfigure(adcBase, adcSampleSeq, 0, adcAnalogInput);
    ADCSequenceStepConfigure(adcBase, adcSampleSeq, 1, adcAnalogInput);
    ADCSequenceStepConfigure(adcBase, adcSampleSeq, 2, adcAnalogInput);
    ADCSequenceStepConfigure(adcBase, adcSampleSeq, 3,
                             adcAnalogInput | ADC_CTL_IE | ADC_CTL_END);

    ADCSequenceEnable(adcBase, adcSampleSeq);
    ADCSequenceDataGet(adcBase, adcSampleSeq, ADCValue);

    IntMasterEnable();
    ui32ADCValue_Avg = (ADCValue[0] + ADCValue[1] + ADCValue[2] + ADCValue[3]
            + 2) / 4;

    return ui32ADCValue_Avg;
}

float ADC::readVolt()
{
    // Scaling the result of the read() function from 4096 steps to 3.3V
    read();
    ADC_Volt = 3.3 * ui32ADCValue_Avg / 4096.0;
    return ADC_Volt;

}
