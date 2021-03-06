#include <drivers.h>

Drivers drivers;

Terminal                  terminal;
Timer                     timer;
TI2C<TGPIOD, 1, 2, 50>    i2c;
IMU                       imu_sensor;
ADC_driver                adc;
LineSensor                line_sensor;
DistanceSensor            distance_sensor;
EncoderSensor             encoder_sensor;
MotorControll             motor_controll;
Key                       key;

Drivers::Drivers()
{

}

Drivers::~Drivers()
{

}

int Drivers::init()
{
  led = 1;

  terminal.init();
  terminal << "\n\n\n#####\n\n\n";
  terminal << "terminal init [DONE]\n"; 

  terminal << "initializing memory ";
  unsigned int mem_res = mem_init();
  terminal << "[DONE], heap start at " << mem_res << "\n"; 

  terminal << "initializing timer ";
  timer.init();
  timer.delay_ms(20);
  terminal << "[DONE]\n";

  terminal << "initializing i2c ";
  i2c.init();
  terminal << "[DONE]\n";

  terminal << "initializing IMU ";
  imu_sensor.init(i2c);
  terminal << " [DONE] with result " << imu_sensor.present() << "\n";


  terminal << "initializing adc ";
  adc.init();
  terminal << "[DONE]\n"; 

  terminal << "initializing line_sensor ";
  line_sensor.init();
  terminal << "[DONE]\n";

  terminal << "initializing distance_sensor ";
  distance_sensor.init();
  terminal << "[DONE]\n";

  terminal << "initializing encoder_sensor ";
  encoder_sensor.init();
  terminal << "[DONE]\n";

  terminal << "initializing motor_controll ";
  motor_controll.init();
  terminal << "[DONE]\n";

  terminal << "initializing key ";
  key.init();
  terminal << "[DONE]\n";

  terminal << "cpu speed set to " << F_CPU/1000000 << " MHz\n";

  terminal << "\n\n";
  terminal << "initializing sequence done\n\n";
  terminal << "motoko uprising ready\n\n";
 
  led = 0; 

  return 0;
}




void Drivers::test_imu_sensor(int count)
{
  terminal << "\test_imu_sensor\n";

  bool run = true;
  while (run)
  {
    if (imu_sensor.ready())
    {
        if (count > 0)
          count--;
        if (count == 0)
          run = false;

        led = 1;

        terminal << imu_sensor.angular_rate.x << " ";
        terminal << imu_sensor.angular_rate.y << " ";
        terminal << imu_sensor.angular_rate.z << " ";

        terminal << " : ";

        terminal << imu_sensor.acceleration.x << " ";
        terminal << imu_sensor.acceleration.y << " ";
        terminal << imu_sensor.acceleration.z << " ";

        terminal << " : ";

        terminal << imu_sensor.angle.x << " ";
        terminal << imu_sensor.angle.y << " ";
        terminal << imu_sensor.angle.z << " ";

        terminal << "\n";

        led = 0;

        timer.delay_ms(200);
    }
  }
}


void Drivers::test_line_sensor(int count)
{
  terminal << "\ntest_line_sensor\n";

  bool run = true;

  line_sensor.on();
  while (run)
  {
    if (line_sensor.ready())
    {
        if (count > 0)
          count--;
        if (count == 0)
          run = false;

        led = 1; 

        terminal << line_sensor.result.on_line_count << " ";
        terminal << line_sensor.result.line_type << " ";
        terminal << line_sensor.result.line_lost_type << " ";
        terminal << line_sensor.result.center_line_position << " ";

        terminal << "\n";

        led = 0;

        timer.delay_ms(200);
    }
  }
  line_sensor.off();
}

void Drivers::test_ir_sensor(int count)
{
    terminal << "\ntest_ir_sensor\n";

    bool run = true;

    Array<int, LINE_SENSOR_COUNT> result;


    line_sensor.on();
    while (run)
    {
        if (line_sensor.ready())
        {
            result = line_sensor.adc_result;

            if (count > 0)
                count--;
            if (count == 0)
                run = false;

            led = 1;

            for (unsigned int i = 0; i < result.size(); i++)
            {
                terminal << result[i] << " ";
            }

            terminal << "\n";

            led = 0;

            timer.delay_ms(200);
      }
    }
    line_sensor.off();
}


void Drivers::test_distance_sensor(int count)
{
  terminal << "\test_distance_sensor\n";

  bool run = true;
  while (run)
  {
    if (distance_sensor.ready())
    {
        if (count > 0)
          count--;
        if (count == 0)
          run = false;

        led = 1;

        distance_sensor.print();

        led = 0;

        timer.delay_ms(200);
    }
  }
}


void Drivers::test_encoder_sensor(int count)
{
  terminal << "\ntest_encoder_sensor\n";

  bool run = true;
  while (run)
  {
        if (count > 0)
          count--;
        if (count == 0)
          run = false;

        led = 1;

        terminal << encoder_sensor.get_left() << " ";
        terminal << encoder_sensor.get_right() << " ";
        terminal << encoder_sensor.get_distance() << " ";

        terminal << "\n";

        led = 0;

        timer.delay_ms(200);
  }
}


void Drivers::test_motor_speed_feedback()
{
  terminal << "\ntest_motor_speed_feedback\n";

  unsigned int cnt = 0;
  float required_left = 0;
  float required_right = 0;

  while (1)
  {
    led = 1;

    motor_controll.set_left_speed(required_left);
    motor_controll.set_right_speed(required_right);

    terminal << required_left << " " << motor_controll.get_left_speed() << " ";
    terminal << required_right << " " << motor_controll.get_right_speed() << "\n";

    led = 0;

    timer.delay_ms(200);

    cnt++;

    switch ((cnt/20)%4)
    {
      case 0: required_left = 0.2; required_right = 0.2; break;
      case 1: required_left = 0.3; required_right = 0.3; break;
      case 2: required_left = 0.5; required_right = 0.5; break;
      case 3: required_left = 0.8; required_right = 0.8; break;
    }
  }
}





void Drivers::test_motor_gyro_feedback()
{
  terminal << "\ntest_motor_gyro_feedback\n";

  PID pid(0.00004, 0.0, 0.0001, 1.0);

  while (1)
  {
    if (imu_sensor.ready())
    {
      led = 1;

      float angle = imu_sensor.angle.z;
      float error = 0.0 - angle;

      float turn = pid.process(error, angle);

      motor_controll.set_left_speed(-turn);
      motor_controll.set_right_speed(turn);

      // terminal << "angle " << angle << "\n";

      led = 0;
    }
  }
}



void Drivers::test_line_follower()
{
  terminal << "\ntest_line_follower\n";

  PID steering_pid(0.16, 0.0, 2.5, 10.0);

  float speed      = 0.0; 
  float speed_max  = 0.4;
  float speed_rise = 0.001;



  while (1)
  {
    if (line_sensor.ready())
    {
        //if (line_sensor.result.line_lost_type == LINE_LOST_NONE)
        if (true)
        {
            //compute line possition and of center error
           float line_position = line_sensor.result.center_line_position;
           float error         = 0.0 - line_position;

           //compute steering using PID
           float steering = steering_pid.process(error, line_position);

           if (speed < speed_max)
            speed+= speed_rise;

           //compute outputs for motors
           float speed_left  = steering  + speed;
           float speed_right = -steering + speed;

           //input into PID controllers for motors
           motor_controll.set_left_speed(speed_left);
           motor_controll.set_right_speed(speed_right);
       }
       else
       {
           motor_controll.set_left_speed(0);
           motor_controll.set_right_speed(0);
           steering_pid.reset();
           speed = 0;
       }
    }
  }
}
