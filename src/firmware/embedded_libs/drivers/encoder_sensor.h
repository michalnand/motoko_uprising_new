#ifndef _ENCODER_SENSOR_H_
#define _ENCODER_SENSOR_H_

#include <gpio.h>

class EncoderSensor
{
  private:
    Gpio<TGPIOC, 6, GPIO_MODE_IN_PULLUP> left_encoder_a;
    Gpio<TGPIOC, 7, GPIO_MODE_IN_PULLUP> left_encoder_b;

    Gpio<TGPIOB, 4, GPIO_MODE_IN_PULLUP> right_encoder_a;
    Gpio<TGPIOB, 5, GPIO_MODE_IN_PULLUP> right_encoder_b;

  public:
    EncoderSensor();
    virtual ~EncoderSensor();

    void init();

    int get_left();
    int get_right();
    int get_distance();

    int get_left_no_atomic();
    int get_right_no_atomic();
};


#endif
