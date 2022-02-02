#ifndef _MATH_H_
#define _MATH_H_

#include "math_t.h"

#define PI              ((float)3.14159265358979323846)
#define SQRT2           ((float)1.4142135623730951)
#define EPSILON         ((float)0.00000001)
#define RAD_TO_DEG      ((float)180.0/PI)
#define DEG_TO_RAD      ((float)PI/180.0)

template<class DType>
struct Vect2d
{   
    DType x, y;
};

template<class DType>
struct Vect3d
{   
    DType x, y, z;
};

template<class DType>
struct Vect4d
{   
    DType x, y, z, w;
};

unsigned int rand();

float fsqrt(float x);

float fsin(float x);
float fcos(float x);
float ftan(float x);
float fsec(float x);

float fasin(float x);
float facos(float x);
float fatan(float x);


float fatan2(float x, float y);

#endif