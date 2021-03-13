#include <motor.h>
#include <stm32f7xx_hal.h>
#include <drivers.h>

#define PWM_FREQUENCY       ((unsigned int)10000)
#define PWM_PRESCALER       ((unsigned int)8)
#define PWM_PERIOD          ((F_CPU/(PWM_FREQUENCY*PWM_PRESCALER*2)) - 1)

Motor::Motor()
{

}

Motor::~Motor()
{

}

void Motor::init()
{
    terminal << "MOTOR PWM init\n";


    terminal << "MOTOR GPIO init\n";

    motor_enable = 1;

    pwm_a_left      = 0;
    pwm_a_right     = 0;

    pwm_b_left.set_af(1);
    pwm_b_right.set_af(1);

/*
    //PWM on pins
    //PE13 - TIM1_CH3, left motor
    //PE11 - TIM1_CH2, right motor
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

    gpioStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_11;
    gpioStructure.GPIO_Mode = GPIO_Mode_AF;
    gpioStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &gpioStructure);
*/
    //terminal << "TIM1 init\n";

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
    outputChannelInit.TIM_OutputNState  = 0;
    outputChannelInit.TIM_OCPolarity    = TIM_OCPolarity_High;
    outputChannelInit.TIM_OCNPolarity   = 0;
    outputChannelInit.TIM_OCIdleState   = 0;
    outputChannelInit.TIM_OCNIdleState  = 0;

    //terminal << "OC3 init\n";

    //pin PE13 config, OC3
    TIM_OC3Init(TIM1, &outputChannelInit);
    TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);
//    GPIO_PinAFConfig(GPIOE, GPIO_PinSource13, 1);

    //terminal << "OC2 init\n";
    //pin PE11 config, OC2
    TIM_OC2Init(TIM1, &outputChannelInit);
    TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
//    GPIO_PinAFConfig(GPIOE, GPIO_PinSource11, 1);

    //terminal << "TIM1 enable\n";
    TIM_CtrlPWMOutputs(TIM1, ENABLE);

//    terminal << "pwm = 0\n";

    run_left(0);
    run_right(0);

//    terminal << "MOTOR init done\n";
}



void Motor::run_left(int pwm)
{
    //check way of motor

    if (pwm > 0)
    {
        //forward
        pwm_a_left = 0;
    }
    else
    {
        //backward
        pwm_a_left = 1;
        pwm = -pwm;
        pwm = MOTOR_SPEED_MAX - pwm;
    }

    //saturation
    if (pwm > MOTOR_SPEED_MAX)
        pwm = MOTOR_SPEED_MAX;

    TIM1->CCR3 = (pwm*(PWM_PERIOD-1))/MOTOR_SPEED_MAX;
}

void Motor::run_right(int pwm)
{
    if (pwm > 0)
    {
        pwm_a_right = 1;
        pwm = MOTOR_SPEED_MAX - pwm;
    }
    else
    {
        pwm_a_right = 0;
        pwm = -pwm;
    }

    //saturation
    if (pwm > MOTOR_SPEED_MAX)
        pwm = MOTOR_SPEED_MAX;

    TIM1->CCR2 = (pwm*(PWM_PERIOD-1))/MOTOR_SPEED_MAX;
}
