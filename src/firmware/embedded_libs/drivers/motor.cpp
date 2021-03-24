#include <motor.h>
#include <stm32f7xx_hal.h>
#include <drivers.h>

#define PWM_FREQUENCY       ((unsigned int)10000)
#define PWM_PRESCALER       ((unsigned int)2) 
#define PWM_PERIOD          (F_CPU*2/(3*PWM_FREQUENCY*PWM_PRESCALER))

Motor::Motor()
{

}

Motor::~Motor()
{

}

void Motor::init()
{
    TIM_TimeBaseInitTypeDef timerInitStructure;
    TIM_OCInitTypeDef outputChannelInit;

    mode            = 1;

    right_pwm       = 0;
    left_pwm        = 0;

    right_pwm.set_af(1);
    left_pwm.set_af(1);


    //init timer
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

    timerInitStructure.TIM_Prescaler        = PWM_PRESCALER;
    timerInitStructure.TIM_CounterMode      = TIM_CounterMode_Up;
    timerInitStructure.TIM_Period           = PWM_PERIOD;
    timerInitStructure.TIM_ClockDivision    = TIM_CKD_DIV2;
    timerInitStructure.TIM_RepetitionCounter = 0;

    TIM_TimeBaseInit(TIM1, &timerInitStructure);
    TIM_Cmd(TIM1, ENABLE);



    outputChannelInit.TIM_OCMode        = TIM_OCMode_PWM1;
    outputChannelInit.TIM_Pulse         = 0;
    outputChannelInit.TIM_OutputState   = TIM_OutputState_Enable; 
    outputChannelInit.TIM_OutputNState  = TIM_OutputNState_Enable;

    outputChannelInit.TIM_OCPolarity = TIM_OCPolarity_Low;
    outputChannelInit.TIM_OCNPolarity = TIM_OCNPolarity_Low;
    outputChannelInit.TIM_OCIdleState = TIM_OCIdleState_Set;
    outputChannelInit.TIM_OCNIdleState = TIM_OCIdleState_Reset;

    //pin PE12 config, OC3
    TIM_OC3Init(TIM1, &outputChannelInit);
    TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);
    //GPIO_PinAFConfig(GPIOE, GPIO_PinSource10, GPIO_AF1_TIM1);
 
    //pin PE11 config, OC2
    TIM_OC2Init(TIM1, &outputChannelInit);
    TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
    //GPIO_PinAFConfig(GPIOE, GPIO_PinSource12, GPIO_AF1_TIM1);

    TIM_CtrlPWMOutputs(TIM1, ENABLE);

    run_left(0); 
    run_right(0);
}



void Motor::run_left(int pwm)
{
    //check way of motor

    if (pwm > 0)
    {
        //forward
        left_way = 0;
    }
    else
    {
        //backward
        left_way = 1;
        pwm = -pwm;
        pwm = MOTOR_SPEED_MAX - pwm;
    }


    pwm = 100;

    //saturation
    if (pwm > MOTOR_SPEED_MAX)
        pwm = MOTOR_SPEED_MAX;

    TIM1->CCR3 = (pwm*PWM_PERIOD)/MOTOR_SPEED_MAX;
}

void Motor::run_right(int pwm)
{
    if (pwm > 0)
    {
        right_way = 1;
        pwm = MOTOR_SPEED_MAX - pwm;
    }
    else
    {
        right_way = 0;
        pwm = -pwm;
    }

    pwm = 200;
  
    //saturation
    if (pwm > MOTOR_SPEED_MAX)
        pwm = MOTOR_SPEED_MAX;


    TIM1->CCR2 = (pwm*PWM_PERIOD)/MOTOR_SPEED_MAX;
}
