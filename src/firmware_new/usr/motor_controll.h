#ifndef _MOTOR_CONTROLL_H_
#define _MOTOR_CONTROLL_H_

#include <low_level_drivers.h>

#define MOTOR_CONTROLL_SAMPLING_MS  ((uint32_t)4)


class MotorControll: public Thread
{
    public:
        MotorControll();
        virtual ~MotorControll();

        void init(float k0, float k1, float k2, float k_diff = 0.1);
        void left_set(float left_required);
        void right_set(float right_required);

        void main();

    private:
        float k0, k1, k2, k_diff;
        
        float left_required, right_required;
        float left_speed, right_speed;
        float left_speed_prev, right_speed_prev;
        float left_speed_diff, right_speed_diff;
};

#endif