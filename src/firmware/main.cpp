#include <clock.h>
#include <drivers.h>
#include <adc_driver.h>

#include <motor.h>

#include <lsm_test.h>
#include <i2c.h>

int main()
{
    core_SystemClock_Config_216();
    //core_SystemClock_Config_312();

    drivers.init();

    key.read();

    terminal << "run\n";


    //drivers.test_imu_sensor();

    //drivers.test_motor_speed_feedback();
    //drivers.test_motor_gyro_feedback();

    //drivers.test_line_follower();

    //drivers.test_motor_gyro_feedback();
    drivers.test_ir_sensor();

    while (1)
    {

    }

    return 0;
}
