#ifndef _MATH_T_H_
#define _MATH_T_H_

template<class DType>
DType abs(DType v)
{
    if (v < 0)
    {
        v = -v;
    }

    return v;
}


template<class DType>
DType min(DType va, DType vb)
{
    if (va < vb)
    {
        return va;
    }
    else
    {
        return vb;
    }
}

template<class DType>
DType max(DType va, DType vb)
{
    if (va > vb)
    {
        return va;
    }
    else
    {
        return vb;
    }
}

template<class DType>
DType sgn(DType v)
{
    if (v > 0)
    {
        return 1.0;
    }
    else
    {
        return -1.0;
    }
}


template<class DType>
DType clamp(DType v, DType min_v, DType max_v)
{
    if (v < min_v)
    {
        v = min_v;
    }

    if (v > max_v)
    {
        v = max_v;
    }

    return v;
}

template<class DType>
DType shrink(DType v, DType s_low, DType s_high)
{
    if (v < s_low || v > s_high)
    {
        return v;
    }
    else
    {
        return 0;
    }
}


/*
    multiply matrix by column vector (single col matrix) and add c vector if any

    result[Mx1] = mat[MxK] * vect[Kx1] + c[Mx1]
    or
    result[M]   = mat[MxK] * vect[K]   + c[M]

    result is column vector with M-elements

    dimensions : 
        mat[M x K]
        vect[K]   (or single col matrix vect[K, 1])
        c[M]      (or single col matrix vect[M, 1]), default nullptr
        result[M] (or single col matrix vect[M, 1])
*/
template<class DType>
void mat_vect_mul(DType *result, DType *mat, DType *vect,  DType *c, unsigned int M, unsigned int K)
{
    if (c == nullptr)
    {
        for (unsigned int m = 0; m < M; m++)
        {
            result[m] = 0;
        }
    }
    else
    {   
        for (unsigned int m = 0; m < M; m++)
        {
            result[m] = c[m];
        }
    }

    for (unsigned int k = 0; k < K; k++)    
    {
        //this loop can be unrolled M-times
        //vect[k] value is M-times resused
        for (unsigned int m = 0; m < M; m++)
        {
            result[m]+= mat[m*K + k]*vect[k];
        }
    }
}


/*
    multiply matrix by column vector (single col matrix) and add c vector if any

    result[Mx1] = mat[MxK] * vect[Kx1] + c[Mx1]
    or
    result[M]   = mat[MxK] * vect[K]   + c[M]

    result is column vector with M-elements

    dimensions : 
        mat[M x K]
        vect[K]   (or single col matrix vect[K, 1])
        c[M]      (or single col matrix vect[M, 1]), default nullptr
        result[M] (or single col matrix vect[M, 1])
*/
template<class DType, unsigned int M, unsigned int K>
void mat_vect_mul(DType *result, DType *mat, DType *vect, DType *c = nullptr)
{
    if (c == nullptr)
    {
        for (unsigned int m = 0; m < M; m++)
        {
            result[m] = 0;
        }
    }
    else
    {   
        for (unsigned int m = 0; m < M; m++)
        {
            result[m] = c[m];
        }
    }

    for (unsigned int k = 0; k < K; k++)    
    {
        //this loop can be unrolled M-times
        //vect[k] value is M-times resused
        for (unsigned int m = 0; m < M; m++)
        {
            result[m]+= mat[m*K + k]*vect[k];
        }
    }
}


#endif