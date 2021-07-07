#include <robot.h>
#include <line_following_config.h>


class LineDetected: public MovementAditionalInterface
{
    public:
        bool step()
        {
            if (line_sensor.result.line_lost_type == LINE_LOST_NONE)
                return true;

            return false;
        }
};

Robot::Robot()
{
    //initialize steering PD controll
    steering_pid.init(STEERING_PID_KP, STEERING_PID_KI, STEERING_PID_KD, STEERING_PID_LIMIT);

    //speed rise limit
    speed_ramp.init(LINE_FOLLOWING_SPEED_RAMP_RISE, 10*LINE_FOLLOWING_SPEED_RAMP_RISE);

    //initialize line curve type predictor using neural network
    //line_predictor.init(cnn);

    steering_filtered = 0.0;
}

Robot::~Robot()
{

}

void Robot::main(unsigned int run_mode)
{
    while (1)
    {
        if (distance_sensor.ready() && distance_sensor.result.front < 0.55)
        {
            allign_to_line(50);

            /*
            if (brick_detection.get() > 0)
                brick_avoid.avoid(BRICK_AVOID_SIDE_LEFT);
            else
                brick_avoid.avoid(BRICK_AVOID_SIDE_RIGHT);
            */


            movement.move(-60,    60,     true);
            movement.move(150,    150,     true);

            motor_controll.set_left_speed(0);
            motor_controll.set_right_speed(0);
            speed_ramp.set(0.0);

            steering_pid.reset(line_sensor.result.center_line_position);
        }
        else
        if (line_sensor.ready())
        {
            if (line_sensor.result.line_lost_type == LINE_LOST_NONE)
            {
                if (line_sensor.result.line_type == LINE_TYPE_SPOT)
                {
                    spot_move();

                    speed_ramp.set(0);

                    steering_pid.reset(line_sensor.result.center_line_position);
                }
                else
                {
                    line_following(run_mode);
                }
            }
            else 
            {
                search_line(line_sensor.result.line_lost_type);
            }
        }
    }
}








void Robot::line_following(unsigned int run_mode)
{
    //set correct speed limit
    float speed_limit = LINE_FOLLOWING_SPEED_MIN;

    if (run_mode == 2)
    {
        /*
        //normalise sensors reading to range <0, 127>
        float min = line_sensor.adc_result[0];
        float max = line_sensor.adc_result[0];

        for (unsigned int i = 0; i < LINE_SENSOR_COUNT; i++)
        {
            if (line_sensor.adc_result[i] < min)
                min = line_sensor.adc_result[i];

            if (line_sensor.adc_result[i] > max)
                max = line_sensor.adc_result[i];
        }

        float k = 0.0, q = 0.0;

        if (max > min)
        {
            k = 127.0/(max - min);
            q = 127.0 - k*max;
        }

        //set model input
        for (unsigned int i = 0; i < LINE_SENSOR_COUNT; i++)
        {
            line_prediction_model.input_buffer()[i] = k*line_sensor.adc_result[i] + q;
        }
        */

        //set model input
        for (unsigned int i = 0; i < LINE_SENSOR_COUNT; i++)
        {
            float tmp = 127*line_sensor.adc_result[i]/1000.0;
            if (tmp < -127)
                tmp = 127;
            if (tmp > 127)
                tmp = 127;
            line_prediction_model.input_buffer()[i] = tmp;
        }

        //process model forward run
        line_prediction_model.forward();

        //argmax - find class ID
        unsigned int class_id = 0;
        for (unsigned int i = 0; i < 3; i++)
        {
            if (line_prediction_model.output_buffer()[i] > line_prediction_model.output_buffer()[class_id])
            {
                class_id = i;
            }
        }

        //set speed limit
        switch (class_id)
        {
            case   0: speed_limit = LINE_FOLLOWING_SPEED_MIN; break;
            case   1: speed_limit = LINE_FOLLOWING_SPEED_MAX; break;
            case   2: speed_limit = LINE_FOLLOWING_SPEED_MIN; break;
        }
    }

    //compute next speed, using ramp and speed limit for this curve
    float speed = speed_ramp.process(speed_limit);

    //get line position and compute error
    float line_position = line_sensor.result.center_line_position;
    float error         = 0.0 - line_position;

    //compute steering using PID
    float steering = steering_pid.process(error, line_position);

    //compute outputs for motors
    float speed_left  = steering  + speed;
    float speed_right = -steering + speed;

    //input into PID controllers for motors
    motor_controll.set_left_speed(speed_left);
    motor_controll.set_right_speed(speed_right);

    steering_filtered = 0.6*steering_filtered + 0.4*steering;
}

void Robot::allign_to_line(unsigned int cycles)
{
    while (cycles)
    {
        if (line_sensor.ready())
        {
            //compute line possition and of center error
            float line_position = line_sensor.result.center_line_position;
            float error         = 0.0 - line_position;

            float steering = steering_pid.process(error, line_position);

            //compute outputs for motors
            float speed_left  = steering  ;
            float speed_right = -steering ;

            //input into PID controllers for motors
            motor_controll.set_left_speed(speed_left);
            motor_controll.set_right_speed(speed_right);

            //set last line position for lost line search
            //line_search.set_last_line_position(line_position);

            cycles--; 
        }
    }

    motor_controll.set_left_speed(0);
    motor_controll.set_right_speed(0);
}



void Robot::spot_move()
{
    int line_position = line_sensor.result.center_line_position;

    motor_controll.set_left_speed(0);
    motor_controll.set_right_speed(0);

    while (true)
    {
        if (line_sensor.ready())
        {
            if (line_position > 0)
            {
                motor_controll.set_right_speed(0);
                motor_controll.set_left_speed(LINE_FOLLOWING_SPEED_MIN);
            }
            else
            {
                motor_controll.set_right_speed(0);
                motor_controll.set_left_speed(LINE_FOLLOWING_SPEED_MIN);
            }

            if (line_sensor.result.on_line_count <= 3)
                break;
        }
    }

    motor_controll.set_left_speed(0);
    motor_controll.set_right_speed(0);
}


void Robot::search_line(unsigned int line_lost_type)
{
    LineDetected line_detected;

 
    if (line_sensor.result.center_line_position > 0.0)
    {
        if (movement.move(0, 130, true, &line_detected) == 1)
            return;

        if (movement.move(0, -130, true, &line_detected) == 1)
            return;

        if (movement.move(130, 0, true, &line_detected) == 1)
            return;

        if (movement.move(-130, 0, true, &line_detected) == 1)
            return;

        if (movement.move(50, 50, true, &line_detected) == 1)
            return;
    }
    else
    {
        if (movement.move(130,  0, true, &line_detected) == 1)
            return;

        if (movement.move(-130, 0, true, &line_detected) == 1)
            return;

        if (movement.move(0, 130, true, &line_detected) == 1)
            return;

        if (movement.move(0, -130, true, &line_detected) == 1)
            return;

        if (movement.move(50, 50, true, &line_detected) == 1)
            return;
    }
}
