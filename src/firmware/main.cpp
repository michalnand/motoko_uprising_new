#include <clock.h>
#include <drivers.h>
#include <diagnostic.h>

#include <tests.h>
#include <robot.h>

int main()
{
    core_SystemClock_Config_216();

    drivers.init();   

    auto key_result = key.read();

    terminal << "run\n";

    //Robot robot;
    //robot.main(key_result);

    //drivers.test_line_sensor();
    //drivers.test_distance_sensor();
    //drivers.test_imu_sensor(); 
    //drivers.test_motor_speed_feedback();
    //drivers.test_motor_gyro_feedback();
    //drivers.test_line_follower();
    //drivers.test_motor_gyro_feedback();

   
    Movement movement; 
    movement.move(-60,    60,     true);
    movement.move(150,    150,     true);
    movement.move(60,    -60,     true);

    
    while(1)
    {

    }

    return 0;
}
