#ifndef _ROBOT_H_
#define _ROBOT_H_

#include <embedded_libs.h>
#include <movement.h>
#include <LinePredictionModel.h>


class Robot
{
    public:
        Robot();
        virtual ~Robot();

        void main(unsigned int run_mode);

    private:
        void line_following(unsigned int run_mode);
        void allign_to_line(unsigned int cycles);
        void spot_move();
        void search_line(unsigned int line_lost_type);

    private:
        PID steering_pid;
        Ramp speed_ramp;

        Movement movement;

        float steering_filtered;

        LinePredictionModel line_prediction_model;
};

#endif
