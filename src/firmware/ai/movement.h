#ifndef _MOVEMENT_H_
#define _MOVEMENT_H_

#include <embedded_libs.h>

class MovementAditionalInterface
{
    public:
        MovementAditionalInterface()
        {

        }

        virtual ~MovementAditionalInterface()
        {

        }

        virtual void start()
        {

        }

        virtual bool step()
        {
            return false;
        }

        virtual void finish()
        {

        }

        virtual float get_left_speed()
        {
            return 0;
        }

        virtual float get_right_speed()
        {
            return 0;
        }
};

class Movement
{
    public:
        Movement();
        virtual ~Movement();
        int move(int left_position, int right_position, bool stop_motors, MovementAditionalInterface *terminate_condition = nullptr);

    private:
        PID left_position_pid;
        PID right_position_pid;


};

#endif
