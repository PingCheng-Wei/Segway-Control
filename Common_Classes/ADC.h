/*
 * ADC.h
 *
 */
#define RCGCADC_BASE 0x400FE000
#define OFFSET_ADC 0x638

#include <stdint.h>
#include <stdbool.h>
#include <System.h>
#include "utils/ustdlib.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/debug.h"
#include "driverlib/hibernate.h"
#include "driverlib/adc.h"

#ifndef ADC_H_
#define ADC_H_

class ADC
{
public:
    ADC();
    virtual ~ADC();

    void init(System *sys, uint32_t base, uint32_t sampleSeq,
              uint32_t analogInput);
    void setHWAveraging(uint32_t averaging);
    uint32_t read();
    float readVolt();

private:
    uint32_t adcBase;
    uint32_t adcSampleSeq;
    uint32_t adcAnalogInput;
    uint32_t ui32ADCValue_Avg;
    uint32_t ADCValue[4];
    float ADC_Volt;
};

#endif /* ADC_H_ */
