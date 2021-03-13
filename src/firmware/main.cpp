#include <clock.h>
#include <drivers.h>
#include <adc_driver.h>
#include <back_led_light.h>

#include <motor.h>

#include <lsm_test.h>
#include <i2c.h>

int main()
{
    core_SystemClock_Config_216();
    //core_SystemClock_Config_312();

    drivers.init();

    BackLedLight bl;
    timer.delay_ms(800);
    bl.set_mode(BL_MODE_BREATH);

    key.read();
    bl.set_mode(BL_MODE_FLASHING_FAST);

    terminal << "run\n";


    TI2C<TGPIOC, 7, 6, 200> i2c_encoder_left;
    TI2C<TGPIOB, 5, 4, 200> i2c_encoder_right;

    i2c_encoder_left.init();
    i2c_encoder_right.init();


    terminal << "encoder i2c init done\n";


    LSM303D encoder_left(i2c_encoder_left);
    LSM303D encoder_right(i2c_encoder_right);


    terminal << "starting test\n";

    while (1) 
    {
        encoder_left.read();
        encoder_right.read();
        /*
        encoder_left.test();
        encoder_right.test();

        terminal << "\n\n\n";

        timer.delay_ms(500);
        */

        terminal << encoder_left.get_orientation() << " " << encoder_right.get_orientation() << "\n";
        timer.delay_ms(50);
    }

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
