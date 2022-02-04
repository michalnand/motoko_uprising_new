#ifndef _MOTOR_DRIVER_H_
#define _MOTOR_DRIVER_H_

#include <gpio.h>

#define MOTOR_PWM_MAX         ((int)255)

class Motor_driver
{
    private:
        Gpio<TGPIOB, 6>                 mode;       //braking mode = 0 or free run = 1

        Gpio<TGPIOE, 11>                right_way;  //way controll RIGHT motor
        Gpio<TGPIOE, 13>                left_way;   //way controll LEFT motor
        Gpio<TGPIOE, 10, GPIO_MODE_AF>  right_pwm;  //TIM1_CH2N pwm  RIGHT motor
        Gpio<TGPIOE, 12, GPIO_MODE_AF>  left_pwm;   //TIM1_CH3N pwm  LEFT motor

    public:
        Motor_driver();
        virtual ~Motor_driver();
        void init();

        void left_set(int pwm);
        void right_set(int pwm);

    private:
        void pwm_init();

    
};

#endif
