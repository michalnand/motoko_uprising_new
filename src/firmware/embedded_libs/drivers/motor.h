#ifndef _MOTOR_H_
#define _MOTOR_H_

#include <gpio.h>

#define MOTOR_SPEED_MAX         ((int)255)

class Motor
{
    private:
        Gpio<TGPIOB, 6> mode;           //braking mode = 0 or free run = 1

        Gpio<TGPIOE, 11>    right_way;    //way controll RIGHT motor
        Gpio<TGPIOE, 13>    left_way;     //way controll LEFT motor
        Gpio<TGPIOE, 10, GPIO_MODE_AF>    right_pwm;    //TIM1_CH2N pwm  RIGHT motor
        Gpio<TGPIOE, 12, GPIO_MODE_AF>    left_pwm;     //TIM1_CH3N pwm  LEFT motor

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
