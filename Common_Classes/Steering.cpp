/*
 * Steering.cpp
 *
 */

#include <Steering.h>

Steering::Steering()
{
    // TODO Auto-generated constructor stub

}

Steering::~Steering()
{
    // TODO Auto-generated destructor stub
}

void Steering::init(System *sys)
{
    //ADC measurement on PE2
    poti.init(sys, ADC1_BASE, 0, ADC_CTL_CH2);
    poti.setHWAveraging(64);

    //Enabling the pin as an input
    potiInput.init(sys, GPIO_PORTE_BASE, GPIO_PIN_1, GPIO_DIR_MODE_IN, true);
    potiInput.setPullup(true);
}

float Steering::getValue()
{
    /*
     * The maximum and minimum values of the steering range are dynamically adjusted
     * if a new higher/lower reading is made.
     *
     * The center point(duty = 0) is in the middle between those two borders
     */
    steeringVolt = poti.readVolt();

    if (steeringVolt < minimum)
    {
        minimum = steeringVolt;
    }

    if (steeringVolt > maximum)
    {
        maximum = steeringVolt;
    }

    center = (maximum + minimum) / 2;

    /* In case of a faulty measurement that results in a duty degree over or under 100% or -100%
     * it is assumed that we are at a maximum or minimum
     *
     * To avoid errors when dividing with 0, the return is set to zero and we avoid that calculation
     *
     * To calculate the duty degree we take the distance between center and measurement and scale it
     * to the distance between both borders. This results in a duty degree between -100% and 100% as needed
     */
    if ((maximum - minimum) == 0)
    {
        return 0.0;
    }
    else if ((steeringVolt - center) * (2 / (maximum - minimum)) <= (-1.0))
    {
        return (-1.0);
    }
    else if ((steeringVolt - center) * (2 / (maximum - minimum)) >= (1.0))
    {
        return 1.0;
    }
    else
    {
        return (steeringVolt - center) * (2 / (maximum - minimum));
    }

}
