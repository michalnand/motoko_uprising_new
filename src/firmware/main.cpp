#include <clock.h>
#include <drivers.h>
#include <diagnostic.h>

int main()
{
    core_SystemClock_Config_216();
    //core_SystemClock_Config_312();

    drivers.init();

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
