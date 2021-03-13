#ifndef _LSM303_D_H_
#define _LSM303_D_H_

#include <i2c.h>
#include <thread.h>

struct sLSM303_3VECT
{
    int32_t x, y, z;
};

class LSM303D
{
    private:
        I2C_Interface *i2c;

        sLSM303_3VECT result;

    public:
        LSM303D(I2C_Interface &i2c_);
        virtual ~LSM303D();

        void read();
        void test();

        int get_orientation();

        sLSM303_3VECT get();
};


#endif
