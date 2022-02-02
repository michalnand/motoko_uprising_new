#ifndef _MOTOR_CONTROLL_H_
#define _MOTOR_CONTROLL_H_


#include <stdint.h>
#include "pid.h"


enum MotorControllMode 
{
    position = 0,
    velocity
};


class MotorControll
{

    public:
        MotorControll();
        virtual ~MotorControll();

        void init_pid(float kp, float ki, float kd, float max_output, float dt);
        void init_constrains(float max_speed_forward, float max_speed_backward, float max_acceleration_forward, float max_acceleration_backward);

        float step(float target_value, int32_t encoder_reading, MotorControllMode mode);


    private:
        PID pid;

};


#endif