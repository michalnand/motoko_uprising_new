#include <clock.h>
#include <drivers.h>
#include <diagnostic.h>

#include <tests.h>

int main()
{
    core_SystemClock_Config_216();

    drivers.init();   

    performance_test(false);
    performance_test(true);

    key.read();

    terminal << "run\n";



    //drivers.test_line_sensor();
    //drivers.test_distance_sensor();


    //drivers.test_imu_sensor();

    //drivers.test_motor_speed_feedback();
    //drivers.test_motor_gyro_feedback();

    //drivers.test_line_follower();

    //drivers.test_motor_gyro_feedback();

    diagnostic();

    while (1)
    {

    }

    return 0;
}
