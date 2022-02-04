#include <motor_controll.h>

#define MOTOR_CONTROLL_SAMPLING_MS  ((uint32_t)4)

MotorControll::MotorControll()
{

}


MotorControll::~MotorControll()
{

}

void MotorControll::init(float k0, float k1, float k2, float k_diff)
{
    this->k0            = k0;
    this->k1            = k1;
    this->k2            = k2;
    this->k_diff        = k_diff;

    left_required       = 0;
    right_required      = 0;

    left_speed          = 0;
    right_speed         = 0;

    left_speed_prev     = 0;
    right_speed_prev    = 0;

    left_speed_diff     = 0;
    right_speed_diff    = 0;

    timer.add_task(this, MOTOR_CONTROLL_SAMPLING_MS);
}


void MotorControll::left_set(float left_required)
{
    this->left_required = left_required;
}


void MotorControll::right_set(float right_required)
{
    this->right_required = right_required;
}
 

void MotorControll::main()
{
    //compute filtered speed derivative (aka. torque)
    left_speed_diff  = (1.0 - k_diff)*left_speed_diff   + k_diff*(left_speed  - left_speed_prev);
    right_speed_diff = (1.0 - k_diff)*right_speed_diff  + k_diff*(right_speed - right_speed_prev);
    
    //2nd order state space controller
    float left_u  = k0*left_required  + k1*left_speed  + k2*left_speed_diff;
    float right_u = k0*right_required + k1*right_speed + k2*right_speed_diff;
    
    //store speed for torque computation 
    left_speed_prev     = left_speed;
    right_speed_prev    = right_speed;
 
    left_speed          = encoder_driver.get_left_speed();
    right_speed         = encoder_driver.get_right_speed();

    //send to motors
    motor_driver.left_set(MOTOR_PWM_MAX*left_u);
    motor_driver.right_set(MOTOR_PWM_MAX*right_u);
}