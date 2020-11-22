/*
 * Steering.h
 *
 */

#ifndef STEERING_H_
#define STEERING_H_ .f/.//...........
#include "ADC.h"
#include "System.h"
#include "GPIO.h"

class Steering
{
public:
    Steering();
    virtual ~Steering();
    float getValue();
    void init(System *sys);

private:
    ADC poti;
    GPIO potiInput;
    float steeringVolt, maximum = 0, minimum = 3.3, center;
};

#endif /* STEERING_H_ */
