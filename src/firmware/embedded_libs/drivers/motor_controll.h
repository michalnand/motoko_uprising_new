#ifndef _MOTOR_CONTROLL_H_
#define _MOTOR_CONTROLL_H_

#include <thread.h>

#include <motor.h>
#include <pid.h>

class MotorControll: public Thread
{
    protected:
        int32_t time_now, time_prev;

        int mode;

        int ml_encoder_prev;
        int mr_encoder_prev;
        int ml_encoder_now;
        int mr_encoder_now;

        float ml_speed,     mr_speed;
        float ml_position,  mr_position;

        float left_speed, right_speed;
        int   left_position, right_position;

    protected:
        Motor motor;
        PID pid_speed_left,     pid_speed_right;
        PID pid_position_left,  pid_position_right;

    public:
        MotorControll();
        virtual ~MotorControll();

        int init();

        void main();

        void set_speed_mode_controll();
        void set_position_mode_controll();

        void set_left_speed(float left_speed);
        void set_right_speed(float right_speed);

        void set_left_position(int left_position);
        void set_right_position(int right_position);

        float get_left_speed();
        float get_right_speed();
};

#endif
