#ifndef _MOTOR_H_
#define _MOTOR_H_

#include <gpio.h>
#include <config.h>

#define MOTOR_SPEED_MAX         ((int)255)

class Motor
{
    private:
          Gpio<TGPIOD, 0, GPIO_MODE_OUT> motor_enable;

          Gpio<TGPIOE, 12, GPIO_MODE_OUT> pwm_a_left;
          Gpio<TGPIOE, 13, GPIO_MODE_AF> pwm_b_left;
          Gpio<TGPIOE, 10, GPIO_MODE_OUT> pwm_a_right;
          Gpio<TGPIOE, 11, GPIO_MODE_AF> pwm_b_right;

        GPIO_InitTypeDef gpioStructure;
        TIM_TimeBaseInitTypeDef timerInitStructure;
        TIM_OCInitTypeDef outputChannelInit;

    public:
        Motor();
        virtual ~Motor();
        void init();

        void run_left(int pwm);
        void run_right(int pwm);

    private:
        void pwm_init();

};

#endif
