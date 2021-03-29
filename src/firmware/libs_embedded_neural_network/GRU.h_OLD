#ifndef _GRU_H_
#define _GRU_H_

#include <stdint.h>
#include <typeinfo>

#include "dot_microkernel.h"



template<class DType>
float _tanh(float value) 
{
    if(value < -3)
        return -1;
    else if(value > 3)
        return 1;
    else
        return value * (27 + value*value)/(27+ 9*value*value);
}


template<class DType>
float _sigmoid(float value) 
{
    float x = value;
    if (x < 0)
        x = -x;

    float x2 = x*x;
    float e = 1.0f + x + x2*0.555f + x2*x2*0.143f;

    return 1.0f / (1.0f + (value > 0 ? 1.0f / e : e));
}

template<class DType, int scale>
float _quantize(float value, float bias)
{
    float result;

    if (typeid(DType) != typeid(float))
        result  = (value*scale)/(128*128*1024.0) + (bias*scale)/(128*1024.0);
    else
        result  = value + bias;
 
    return result;
}



template<   unsigned int in_features, unsigned int hidden_size, 
            class IO_t, class WEIGHT_t, class ACC_t, int io_max, 
            int hr_scale, int hz_scale, int hn_scale,
            int ir_scale, int iz_scale, int in_scale>
void GRUStep(float *hidden_buffer_next, float *hidden_buffer, IO_t *input_buffer,
             
            const WEIGHT_t *whr, const WEIGHT_t *bhr,
            const WEIGHT_t *whz, const WEIGHT_t *bhz,
            const WEIGHT_t *whn, const WEIGHT_t *bhn,

            const WEIGHT_t *wir, const WEIGHT_t *bir,
            const WEIGHT_t *wiz, const WEIGHT_t *biz,
            const WEIGHT_t *win, const WEIGHT_t *bin )
{
    IO_t hidden_buffer_quant[hidden_size];

    for (unsigned int i = 0; i < hidden_size; i++)
    {
        if (typeid(IO_t) == typeid(float))
            hidden_buffer_quant[i] = hidden_buffer[i];
        else
            hidden_buffer_quant[i] = (IO_t)(hidden_buffer[i]*127.0);
    } 

    for (unsigned int i = 0; i < hidden_size; i++)
    {       
        float ra  = dot_microkernel<hidden_size, WEIGHT_t, IO_t, ACC_t>(whr + i*hidden_size, hidden_buffer_quant);
        ra = _quantize<IO_t, hr_scale>(ra, bhr[i]);
        
        float rb  = dot_microkernel<in_features, WEIGHT_t, IO_t, ACC_t>(wir + i*in_features, input_buffer);
        rb = _quantize<IO_t, hr_scale>(rb, bir[i]);
        
        float r = _sigmoid<float>(ra + rb);


        float za  = dot_microkernel<hidden_size, WEIGHT_t, IO_t, ACC_t>(whz + i*hidden_size, hidden_buffer_quant);
        za = _quantize<IO_t, hz_scale>(za, bhz[i]);
        
        float zb  = dot_microkernel<in_features, WEIGHT_t, IO_t, ACC_t>(wiz + i*in_features, input_buffer);
        zb = _quantize<IO_t, iz_scale>(zb, biz[i]);

        float z = _sigmoid<float>(za + zb);
 

        float na  = dot_microkernel<hidden_size, WEIGHT_t, IO_t, ACC_t>(whn + i*hidden_size, hidden_buffer_quant);
        na = _quantize<IO_t, hn_scale>(na, bhn[i]);

        float nb  = dot_microkernel<in_features, WEIGHT_t, IO_t, ACC_t>(win + i*in_features, input_buffer);
        nb = _quantize<IO_t, in_scale>(nb, bin[i]);
        
        float n = _tanh<float>(r*na + nb); 

        hidden_buffer_next[i] = (1.0 - z)*n + z*hidden_buffer[i];
    }
}

template<   unsigned int in_features, unsigned int hidden_size, 
            class IO_t, class WEIGHT_t, class ACC_t, int io_max, 
            int hr_scale, int hz_scale, int hn_scale,
            int ir_scale, int iz_scale, int in_scale>
void GRU(   IO_t *output_buffer, IO_t *input_buffer, unsigned int sequence_length,
            
            const WEIGHT_t *whr, const WEIGHT_t *bhr,
            const WEIGHT_t *whz, const WEIGHT_t *bhz,
            const WEIGHT_t *whn, const WEIGHT_t *bhn,

            const WEIGHT_t *wir, const WEIGHT_t *bir,
            const WEIGHT_t *wiz, const WEIGHT_t *biz,
            const WEIGHT_t *win, const WEIGHT_t *bin )
{ 
    float hidden_buffer[hidden_size];
    float hidden_buffer_next[hidden_size];

    for (unsigned int i = 0; i < hidden_size; i++)
    {
        hidden_buffer[i]       = 0;
        hidden_buffer_next[i]  = 0;
    }

    for (unsigned int t = 0; t < sequence_length; t++)
    {    
        GRUStep<in_features, hidden_size,  IO_t, WEIGHT_t, ACC_t, io_max, 
                hr_scale,   hz_scale,     hn_scale,
                ir_scale,   iz_scale,     in_scale>(   
                    hidden_buffer_next, hidden_buffer, input_buffer + t*in_features,
                    whr, bhr,
                    whz, bhz,
                    whn, bhn,

                    wir, bir,
                    wiz, biz,
                    win, bin 
        ); 

        for (unsigned int i = 0; i < hidden_size; i++)
            hidden_buffer[i] = hidden_buffer_next[i];
    }
   
    for (unsigned int i = 0; i < hidden_size; i++)
    {
        if (typeid(IO_t) == typeid(float))
            output_buffer[i] = hidden_buffer[i];
        else
            output_buffer[i] = (IO_t)(hidden_buffer[i]*127.0);
    }
}


#endif