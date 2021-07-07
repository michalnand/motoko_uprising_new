#ifndef _ROBOT_CONFIG_H_
#define _ROBOT_CONFIG_H_

#define MOTOR_CONTROLL_DT               LINE_SENSOR_DT
#define MOTOR_CONTROLL_SPEED_PID_KP     ((float)1.7) 
#define MOTOR_CONTROLL_SPEED_PID_KI     ((float)0.1)
#define MOTOR_CONTROLL_SPEED_PID_KD     ((float)1.5)


#define MOTOR_CONTROLL_POSITION_PID_KP  ((float)0.01) 
#define MOTOR_CONTROLL_POSITION_PID_KI  ((float)0.0)
#define MOTOR_CONTROLL_POSITION_PID_KD  ((float)0.01)
 

#define MOVEMENT_FORWARD_POSITION_PID_KP         ((float)0.01) 
#define MOVEMENT_FORWARD_POSITION_PID_KI         ((float)0.0001)
#define MOVEMENT_FORWARD_POSITION_PID_KD         ((float)0.02)
#define MOVEMENT_FORWARD_POSITION_PID_RANGE      ((float)1.0)

#define MOVEMENT_FORWARD_STEERING_PID_KP         ((float)0.001)
#define MOVEMENT_FORWARD_STEERING_PID_KI         ((float)0.0)
#define MOVEMENT_FORWARD_STEERING_PID_KD         ((float)0.001)
#define MOVEMENT_FORWARD_STEERING_PID_RANGE      ((float)2.0)

 
#define MOVEMENT_RAMP_UP        ((float)0.005)
#define MOVEMENT_RAMP_DOWN      ((float)0.05)  
#define MOVEMENT_SPEED          ((float)0.6)


#endif
