#include <movement.h>
#include <robot_config.h>

Movement::Movement()
{
    left_position_pid.init(MOVEMENT_FORWARD_POSITION_PID_KP, MOVEMENT_FORWARD_POSITION_PID_KI, MOVEMENT_FORWARD_POSITION_PID_KD, MOVEMENT_FORWARD_POSITION_PID_RANGE);
    right_position_pid.init(MOVEMENT_FORWARD_POSITION_PID_KP, MOVEMENT_FORWARD_POSITION_PID_KI, MOVEMENT_FORWARD_POSITION_PID_KD, MOVEMENT_FORWARD_POSITION_PID_RANGE);
}

Movement::~Movement()
{

}

int Movement::move(int left_position, int right_position, bool stop_motors, MovementAditionalInterface *terminate_condition)
{
    int target_left_position  = left_position  + encoder_sensor.get_left();
    int target_right_position = right_position + encoder_sensor.get_right();
        
    if ( stop_motors || (left_position < 0) || (right_position < 0) )
    {
        motor_controll.set_left_speed(0.0);
        motor_controll.set_right_speed(0.0); 

        while ( (abs(motor_controll.get_left_speed()) > 0.02) || (abs(motor_controll.get_right_speed()) > 0.02) )
        {
           timer.delay_ms(10); 
        }

        timer.delay_ms(100); 
    }

    Ramp left_ramp;  
    if (left_position > 0)
        left_ramp.init(MOVEMENT_RAMP_UP, MOVEMENT_RAMP_DOWN, motor_controll.get_left_speed());
    else
        left_ramp.init(MOVEMENT_RAMP_UP, MOVEMENT_RAMP_UP*0.8, 0*motor_controll.get_left_speed());
   
    Ramp right_ramp; 
    if (right_position > 0)
        right_ramp.init(MOVEMENT_RAMP_UP, MOVEMENT_RAMP_DOWN, motor_controll.get_right_speed());
    else
        right_ramp.init(MOVEMENT_RAMP_UP, MOVEMENT_RAMP_UP*0.8, 0*motor_controll.get_right_speed());

    int result = -1;

    if (terminate_condition != nullptr)
        terminate_condition->start();

    bool terminate = false;

    while (terminate == false) 
    {
        int left_position   = encoder_sensor.get_left();
        int right_position  = encoder_sensor.get_right();

        int left_error      = target_left_position  - left_position;
        int right_error     = target_right_position - right_position;

        float left_speed    = left_position_pid.process(left_error,   left_error);
        float right_speed   = right_position_pid.process(right_error, right_error);

        float left_speed_ext    = 0.0;
        float right_speed_ext   = 0.0; 

        if (terminate_condition != nullptr)
        {
            terminate       = terminate_condition->step();
            left_speed_ext  = terminate_condition->get_left_speed();
            right_speed_ext = terminate_condition->get_right_speed();
        }

        left_speed          = left_ramp.process(left_speed    + left_speed_ext);
        right_speed         = right_ramp.process(right_speed  + right_speed_ext);
 
        motor_controll.set_left_speed(left_speed);
        motor_controll.set_right_speed(right_speed);

        if (abs(left_error) < 5.0 && abs(right_error) < 5.0)
        {
            break;
        } 

        timer.delay_ms(10);
    }  

    if (stop_motors == true && terminate == false)
    {
        motor_controll.set_left_speed(0.0);
        motor_controll.set_right_speed(0.0);  

        while ( (abs(motor_controll.get_left_speed()) > 0.02) || (abs(motor_controll.get_right_speed()) > 0.02) )
        {
           timer.delay_ms(10); 
        }

        timer.delay_ms(100); 
    }

    if (terminate_condition != nullptr)
        terminate_condition->finish();

    if (terminate)
        return 1;
    else
        return 0;
}
