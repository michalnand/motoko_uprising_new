#ifndef _GRU_H_
#define _GRU_H_

#include <stdint.h>
#include "Linear.h"

template<class DType>
float _tanh(float value) 
{
    if(value < -3)
        return -1;
    else if(value > 3)
        return 1;
    else
        return value * (27 + value*value)/(27 + 9*value*value);
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


template<class ACC_t>
float _quantize(ACC_t a, ACC_t b)
{
    float result; 
    result  = ((float)a + (float)b)/(128.0);
    return result;
}


template<   unsigned int in_features, unsigned int hidden_size, 
            class IO_t, class WEIGHT_t, class ACC_t, int io_max, 
            int hr_scale, int hz_scale, int hn_scale,
            int ir_scale, int iz_scale, int in_scale>
void GRUStream(IO_t *output_buffer, IO_t *input_buffer, float *hidden_buffer,
             
            const WEIGHT_t *whr, const WEIGHT_t *bhr,
            const WEIGHT_t *whz, const WEIGHT_t *bhz,
            const WEIGHT_t *whn, const WEIGHT_t *bhn,

            const WEIGHT_t *wir, const WEIGHT_t *bir,
            const WEIGHT_t *wiz, const WEIGHT_t *biz,
            const WEIGHT_t *win, const WEIGHT_t *bin )
{
    IO_t hidden_buffer_quant[hidden_size];

    ACC_t hr[hidden_size];
    ACC_t ir[hidden_size]; 

    ACC_t hz[hidden_size];
    ACC_t iz[hidden_size]; 

    ACC_t hn[hidden_size];
    ACC_t in[hidden_size]; 

    for (unsigned int i = 0; i < hidden_size; i++)
    {
        if (sizeof(IO_t) == 1)
            hidden_buffer_quant[i] = (IO_t)(hidden_buffer[i]*127.0);
        else
            hidden_buffer_quant[i] = hidden_buffer[i];
    } 
 
    LinearACC<hidden_size, hidden_size, IO_t, WEIGHT_t, ACC_t, hr_scale>(hr, hidden_buffer_quant, whr, bhr);
    LinearACC<in_features, hidden_size, IO_t, WEIGHT_t, ACC_t, ir_scale>(ir, input_buffer, wir, bir);

    LinearACC<hidden_size, hidden_size, IO_t, WEIGHT_t, ACC_t, hz_scale>(hz, hidden_buffer_quant, whz, bhz);
    LinearACC<in_features, hidden_size, IO_t, WEIGHT_t, ACC_t, iz_scale>(iz, input_buffer, wiz, biz);
    
    LinearACC<hidden_size, hidden_size, IO_t, WEIGHT_t, ACC_t, hn_scale>(hn, hidden_buffer_quant, whn, bhn);
    LinearACC<in_features, hidden_size, IO_t, WEIGHT_t, ACC_t, in_scale>(in, input_buffer, win, bin);

    if (sizeof(IO_t) == 1)
    {
        for (unsigned int i = 0; i < hidden_size; i++)
        {
            float r = _sigmoid<float>(  _quantize<ACC_t>(hr[i], ir[i]));
            float z = _sigmoid<float>(  _quantize<ACC_t>(hz[i], iz[i]));
            float n = _tanh<float>(     _quantize<ACC_t>(r*hn[i], in[i])); 
    
            hidden_buffer[i] = (1.0 - z)*n + z*hidden_buffer[i];
        } 
    }
    else
    {
        for (unsigned int i = 0; i < hidden_size; i++)
        {
            float r = _sigmoid<float>(hr[i] + ir[i]);
            float z = _sigmoid<float>(hz[i] + iz[i]);
            float n = _tanh<float>(r*hn[i] + in[i]); 
    
            hidden_buffer[i] = (1.0 - z)*n + z*hidden_buffer[i];
        } 
    }

    for (unsigned int i = 0; i < hidden_size; i++)
    {
        if (sizeof(IO_t) == 1)
            output_buffer[i] = (IO_t)(hidden_buffer[i]*127.0);
        else
            output_buffer[i] = hidden_buffer[i];
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

    for (unsigned int i = 0; i < hidden_size; i++)
    {
        hidden_buffer[i]       = 0;
    }

    for (unsigned int t = 0; t < sequence_length; t++)
    {    
        GRUStream<in_features, hidden_size,  IO_t, WEIGHT_t, ACC_t, io_max, 
                hr_scale,   hz_scale,     hn_scale,
                ir_scale,   iz_scale,     in_scale>(   
                    output_buffer, input_buffer + t*in_features, hidden_buffer,
                    whr, bhr,
                    whz, bhz,
                    whn, bhn,

                    wir, bir,
                    wiz, biz,
                    win, bin 
        ); 
    }
}


#endif