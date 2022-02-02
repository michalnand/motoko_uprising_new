#include "imu.h"


IMU::IMU()
{
    result.x = 0;
    result.y = 0;
    result.z = 0;

    this->alpha = 0.1;
}

IMU::~IMU()
{

}

void IMU::init(float alpha)
{
    result.x = 0;
    result.y = 0;
    result.z = 0;

    this->alpha = alpha;
}

Vect3d<float> IMU::step(float ax, float ay, float az, float gx, float gy, float gz, float dt)
{
    ax = clamp(ax, -G_const, G_const);
    ay = clamp(ay, -G_const, G_const);
    az = clamp(az, -G_const, G_const);

    Vect3d<float> acc_result;

    acc_result.x = -fatan2(az, ay);      //roll
    acc_result.y = fasin(ax/G_const);    //pitch
    acc_result.z = 0;                    //yaw
    
    //shrink small noise
    gx = -shrink(gx, -0.01f, 0.01f);
    gy = -shrink(gy, -0.01f, 0.01f);
    gz =  shrink(gz, -0.01f, 0.01f);

    Vect3d<float> gyro_result;

    gyro_result = convert_euler_angles(result.x, result.y, gx, gy, gz);

    //complementary filter
    result.x = alpha*acc_result.x   + (1.0 - alpha)*(result.x + gyro_result.x*dt);
    result.y = alpha*acc_result.y   + (1.0 - alpha)*(result.y + gyro_result.y*dt);
    result.z = result.z             + gyro_result.z*dt;
    

    return result;
}


Vect3d<float> IMU::convert_euler_angles(float phi, float theta, float p, float q, float r)
{
    Vect3d<float> result;

    float sin_phi   = fsin(phi);
    float cos_phi   = fcos(phi);
    float tan_theta = ftan(theta);
    float sec_theta = fsec(theta); 

    result.x        = p +  sin_phi*tan_theta*q + cos_phi*tan_theta*r;
    result.y        =      cos_phi*q           - sin_phi*r;
    result.z        =      sin_phi*sec_theta*q + cos_phi*sec_theta*r;

    return result;
}


