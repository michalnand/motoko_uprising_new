#include "fmath.h"
#include <stdint.h>


unsigned int g_rand = 0;

unsigned int rand()
{
    g_rand = 1103515245*g_rand + 12345;

    return g_rand;
}

float fsqrt(float x)
{   
    if (x <= 0)
    {
        return 0;
    }

    float result = x/2;

    for (unsigned int i = 0; i < 16; i++)
    {
        result = 0.5*(result + (x / result));
    }

    return result;
}

//compute sin(x) fitted into -pi2/, pi/2
float fsin_pi(float x)
{
    //fit x into interval -pi/2, pi/2
    // be close to zero for taylor series
    int32_t cnt  = x/(0.5*PI);
    float x_norm = x - 0.5*PI*cnt;
 
    float res = 0, pow = x_norm, fact = 1;
    for(int i = 0; i < 6; i++)
    {
        res+=pow/fact;
        
        pow*=-1*x_norm*x_norm;

        fact*=(2*(i+1))*(2*(i+1)+1);
    }

    return res;
}

float fsin(float x)
{   
    //fit x into interval -2*pi, 2*pi
    int32_t cnt  = x/(2*PI);
    float x_norm = x - 2*PI*cnt;

    float neg_flag;

    //fit into interval 0, 2*pi
    if (x_norm < 0)
    {
        x_norm   = -x_norm;
        neg_flag = -1;
    }
    else
    {
        neg_flag = 1;
    }

    float result;
    if (x_norm < PI/2)
    {
        result = fsin_pi(x_norm);
    }
    else if (x_norm < 3.0*PI/2.0)
    {
        result = -fsin_pi(x_norm - PI);
    }
    else
    {
        result = fsin_pi(x_norm - 2.0*PI);
    }
    

    return neg_flag*result;
}

float fcos(float x)
{
    return fsin(x + PI/2);
}

float ftan(float x)
{
    float tmp = fcos(x);
    if (tmp == 0)
    {
        tmp = EPSILON;
    }

    return fsin(x)/tmp;

    //float y = (1 - x*x);
    //return x * (((-0.000221184 * y + 0.0024971104) * y - 0.02301937096) * y + 0.3182994604 + 1.2732402998 / y);
}


float fsec(float x)
{
    float tmp = fcos(x);

    if (tmp < EPSILON && tmp > -EPSILON)
    {
        if (tmp > 0)
        {
            return 1.0/EPSILON;
        }
        else
        {
            return -1.0/EPSILON;
        }
    }
    else
    {
        return 1.0/tmp;
    }
}


float fasin_(float x)
{
    return fatan(x/fsqrt(1.0 - x*x));
}


float fasin(float x)
{ 
    x = clamp(x, -1.0f, 1.0f);

    if (abs(x) <= 1.0/SQRT2)
    {
        return fasin_(x);
    }

    if (x > 1.0/SQRT2)
    {
        return PI/2 - fasin_(fsqrt(1.0 - x*x));
    }

    if (x < -1.0/SQRT2)
    {
        return -PI/2 + fasin_(fsqrt(1.0 - x*x));
    }

    return 1000;
} 



float facos(float x)
{
    return PI/2.0 - fasin(x);
}




float fatan(float x) 
{
    //http://pubs.opengroup.org/onlinepubs/009695399/functions/atan2.html


    if (x > 1.0)
    {
        return PI/2 - fatan(1.0/x);
    }  
    else if (x < -1.0)
    {
        return -PI/2 - fatan(1.0/x);
    }


    float xx  = x * x;
    float a   = 0.0776509570923569;
    float b   = -0.287434475393028;
    float c   = PI/4.0 - a - b;

    return ((a*xx + b)*xx + c)*x;
}

float fatan2(float x, float y)
{
    if (x == 0 && y == 0)
    {
        return 0; 
    }

    auto a = min(abs(x), abs(y))/max(abs(x), abs(y));
    auto s = a*a;

    auto result = ((-0.0464964749 * s + 0.15931422) * s - 0.327622764) * s * a + a;

    if (abs(y) > abs(x))
    {
        result = 1.57079637 - result;
    }

    if (x < 0)
    {
        result = 3.14159274 - result;
    }

    if (y < 0)
    {
        result = -result;
    }

    return result;
}