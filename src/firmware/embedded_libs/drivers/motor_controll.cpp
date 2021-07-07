#include <motor_controll.h>
#include <drivers.h>


#define MOTOR_CONTROLL_SPEED_MAX        ((float)1.0/0.6)


MotorControll::MotorControll()
{

}

MotorControll::~MotorControll()
{

}

int MotorControll::init()
{
    motor.init();

    pid_speed_left.init(    MOTOR_CONTROLL_SPEED_PID_KP,
                            MOTOR_CONTROLL_SPEED_PID_KI,
                            MOTOR_CONTROLL_SPEED_PID_KD,
                            1.0);

    pid_speed_right.init(   MOTOR_CONTROLL_SPEED_PID_KP,
                            MOTOR_CONTROLL_SPEED_PID_KI,
                            MOTOR_CONTROLL_SPEED_PID_KD,
                            1.0);


    pid_position_left.init(     MOTOR_CONTROLL_POSITION_PID_KP,
                                MOTOR_CONTROLL_POSITION_PID_KI,
                                MOTOR_CONTROLL_POSITION_PID_KD,
                                10.0);

    pid_position_right.init(    MOTOR_CONTROLL_POSITION_PID_KP,
                                MOTOR_CONTROLL_POSITION_PID_KI,
                                MOTOR_CONTROLL_POSITION_PID_KD,
                                10.0);

    time_now        = timer.get_time();
    time_prev       = time_now;

    set_speed_mode_controll();

    ml_encoder_prev = 0;
    mr_encoder_prev = 0;
    ml_encoder_now  = 0;
    mr_encoder_now  = 0;

    ml_speed        = 0;
    mr_speed        = 0;

    left_speed      = 0;
    right_speed     = 0;

    left_position   = 0;
    right_position  = 0;

    timer.add_task(this, MOTOR_CONTROLL_DT, false);

    return 0;
}

void MotorControll::set_speed_mode_controll()
{
    mode = 0;
}

void MotorControll::set_position_mode_controll()
{
    mode = 1;
}

void MotorControll::set_left_speed(float left_speed)
{
    this->left_speed = left_speed;
}

void MotorControll::set_right_speed(float right_speed)
{
    this->right_speed = right_speed;
}

void MotorControll::set_left_position(int left_position)
{
    this->left_position      = left_position;
}

void MotorControll::set_right_position(int right_position)
{
    this->right_position     = right_position;
}



float MotorControll::get_left_speed()
{
    return ml_speed;
}

float MotorControll::get_right_speed()
{
    return mr_speed;
}

void MotorControll::main()
{
    float kf = 0.1;

    time_prev   = time_now;
    time_now    = timer.get_time_interrupt();
    int32_t dt  = time_now - time_prev;
    if (dt == 0)
        dt = 1;

    ml_encoder_prev = ml_encoder_now;
    mr_encoder_prev = mr_encoder_now;

    ml_encoder_now = encoder_sensor.get_left_no_atomic();
    mr_encoder_now = encoder_sensor.get_right_no_atomic();

    ml_speed    = (1.0 - kf)*ml_speed + kf*(ml_encoder_now - ml_encoder_prev)*MOTOR_CONTROLL_SPEED_MAX/dt;
    mr_speed    = (1.0 - kf)*mr_speed + kf*(mr_encoder_now - mr_encoder_prev)*MOTOR_CONTROLL_SPEED_MAX/dt;

    ml_position = (1.0 - kf)*ml_position + kf*ml_encoder_now;
    mr_position = (1.0 - kf)*mr_position + kf*mr_encoder_now;

    int ml_vu = MOTOR_SPEED_MAX*pid_speed_left.process (left_speed  - ml_speed, ml_speed);
    int mr_vu = MOTOR_SPEED_MAX*pid_speed_right.process(right_speed - mr_speed, mr_speed);

    int ml_pu = MOTOR_SPEED_MAX*pid_position_left.process (left_position  - ml_position, ml_position);
    int mr_pu = MOTOR_SPEED_MAX*pid_position_right.process(right_position - mr_position, mr_position);

    if (mode == 0)
    {
        motor.run_left(ml_vu); 
        motor.run_right(mr_vu);
    }
    else if (mode == 1)
    {
        motor.run_left(ml_pu); 
        motor.run_right(mr_pu);
    }
}
