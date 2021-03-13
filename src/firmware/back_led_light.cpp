#include "back_led_light.h"

#define PWM_MAX     ((unsigned int)7)
#define PATTERN_LENGTH 15

const unsigned char breath_pattern[PATTERN_LENGTH] = {0, 1, 2, 3, 4, 5, 6, 7, 6, 5, 4, 3, 2, 1, 0};


BackLedLight::BackLedLight()
{
    set_mode(BL_MODE_FLASHING_START);
    timer.add_task(this, 1, false);
}

BackLedLight::~BackLedLight()
{

}

void BackLedLight::set_mode(unsigned int mode)
{
    cnt = 0;
    this->mode = mode;
    time_start = timer.get_time();
}

void BackLedLight::main()
{
    if (mode == BL_MODE_OFF)
        led_back = 0;

    if (mode == BL_MODE_ON)
        led_back = 1;

    if (mode == BL_MODE_FLASHING)
    {
        if ((cnt%100) == 0)
          led_back = 1;
        else
          led_back = 0; 
    }

    if (mode == BL_MODE_FLASHING_FAST)
    {
        if ((cnt%50) == 0)
          led_back = 1;
        else
          led_back = 0;
    }

    if (mode == BL_MODE_FLASHING_START)
    {
        if (timer.get_time() > 800+time_start)
          mode = BL_MODE_ON;
        else
        {
          if ((cnt%100) < 25)
            led_back = 1;
          else
            led_back = 0;
        }
    }

    if (mode == BL_MODE_BREATH)
    {
        unsigned int pwm_phase = cnt&PWM_MAX;

        unsigned int pwm_set = breath_pattern[(cnt/50)%PATTERN_LENGTH];

        if (pwm_phase < pwm_set)
            led_back = 1;
        else
            led_back = 0;

    }


    cnt++;
}
