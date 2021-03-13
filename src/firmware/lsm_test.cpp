#include "lsm_test.h"
#include <drivers.h>

#define LSM303D_I2C_ADDRESS     ((unsigned char)0x3C) //0x3A

#define OUT_X_L_M       ((unsigned char)0x28)
#define OUT_X_H_M       ((unsigned char)0x29)
#define OUT_Y_L_M       ((unsigned char)0x2A)
#define OUT_Y_H_M       ((unsigned char)0x2B)
#define OUT_Z_L_M       ((unsigned char)0x2C)
#define OUT_Z_H_M       ((unsigned char)0x2D)

#define CTRL1           ((unsigned char)0x20)
#define CTRL2           ((unsigned char)0x21)
#define CTRL3           ((unsigned char)0x22)
#define CTRL4           ((unsigned char)0x23)
#define CTRL5           ((unsigned char)0x24)

#define WHO_AM_I           ((unsigned char)0x0F)


LSM303D::LSM303D(I2C_Interface &i2c_)
{
        i2c = &i2c_;

        terminal << "lsm init\n";

        i2c->write_reg(LSM303D_I2C_ADDRESS, CTRL1, (1<<6)|(1<<5)|(1<<2)|(1<<3)|(1<<4));
        i2c->write_reg(LSM303D_I2C_ADDRESS, CTRL3, 0);
        i2c->write_reg(LSM303D_I2C_ADDRESS, CTRL4, (1<<2)|(1<<3));

        result.x = 0;
        result.y = 0;
        result.z = 0;

        terminal << "lsm init done \n\n";
}



LSM303D::~LSM303D()
{

}

void LSM303D::read()
{
    i2c->start();
    i2c->write(LSM303D_I2C_ADDRESS);
    i2c->write(OUT_X_L_M);

    i2c->start();
    i2c->write(LSM303D_I2C_ADDRESS|0x01); // slave address, read command

    int16_t x, y, z;
    
    x = ((int16_t)i2c->read(1)) << 0;
    x|= ((int16_t)i2c->read(1)) << 8;

    y = ((int16_t)i2c->read(1)) << 0;
    y|= ((int16_t)i2c->read(1)) << 8;

    z = ((int16_t)i2c->read(1)) << 0;
    z|= ((int16_t)i2c->read(0)) << 8;

    i2c->stop();

    result.x = x;
    result.y = y;
    result.z = z;
}

void LSM303D::test()
{
    unsigned char who_am_i_result = this->i2c->read_reg(LSM303D_I2C_ADDRESS, WHO_AM_I); //61 OK

    terminal << "who_am_i_result " << who_am_i_result << "\n";

    read();

    terminal << "[" << result.x << " " << result.y << " " << result.z << "]\n";
}

int LSM303D::get_orientation()
{
    if (result.z > 0)
        return 1;
    return -1;
}

sLSM303_3VECT LSM303D::get()
{
    return result;
}
