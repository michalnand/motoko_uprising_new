#ifndef _ENCODER_DRIVER_H_
#define _ENCODER_DRIVER_H_

#include <gpio.h>
#include <thread.h>


//encoder sensor config
#define ENCODER_DRIVER_PULSES_PER_ROTATION  ((int32_t)180*2)
#define ENCODER_DRIVER_WHEEL_CIRCUMFERENCE  ((int32_t)88)

#define ENCODER_FILTER_K                    ((float)0.9)
#define ENCODER_SAMPLING_MS                 ((int32_t)1)
 

class EncoderDriver: public Thread
{
  private:
    Gpio<TGPIOC, 6, GPIO_MODE_IN_PULLUP> left_encoder_a;
    Gpio<TGPIOC, 7, GPIO_MODE_IN_PULLUP> left_encoder_b;

    Gpio<TGPIOB, 4, GPIO_MODE_IN_PULLUP> right_encoder_a;
    Gpio<TGPIOB, 5, GPIO_MODE_IN_PULLUP> right_encoder_b;

  public: 
    EncoderDriver();
    virtual ~EncoderDriver();

    void init();

    int get_left();
    int get_right();
    int get_distance();

    float get_left_speed();
    float get_right_speed();

    int get_left_no_atomic();
    int get_right_no_atomic();

    void main();
};


#endif
