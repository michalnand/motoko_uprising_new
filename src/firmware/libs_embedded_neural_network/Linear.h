#ifndef _LINEAR_H_
#define _LINEAR_H_

#include <stdint.h>

#define LINEAR_TILE_ROWS    ((unsigned int)8)
#define LINEAR_TILE_COLS    ((unsigned int)4)

template<   unsigned int in_features, unsigned int out_features, 
            class IO_t, class WEIGHT_t, class ACC_t, int scale>
inline
void LinearACC(ACC_t *output_buffer, IO_t *input_buffer, const WEIGHT_t *weights, const WEIGHT_t *bias)
{ 
    for (unsigned int j = 0; j < out_features; j++)
    {
        output_buffer[j] = 0;
    }

    /*
    //naive code
    for (unsigned int i = 0; i < in_features; i++)
        for (unsigned int j = 0; j < out_features; j++)
            output_buffer[j]+= weights[j*in_features + i]*input_buffer[i]; 
    */
    
    //tiling
    for (unsigned int i = 0; i < in_features; i+= LINEAR_TILE_COLS)
        for (unsigned int j = 0; j < out_features; j+= LINEAR_TILE_ROWS)
            for (unsigned int jj = 0; jj < LINEAR_TILE_ROWS; jj++)
                for (unsigned int ii = 0; ii < LINEAR_TILE_COLS; ii++)
                    output_buffer[j + jj]+= weights[(j + jj)*in_features + i + ii]*input_buffer[i + ii]; 
    
    
    for (unsigned int j = 0; j < out_features; j++)
    {
        ACC_t result = output_buffer[j];

        //check if input is int8 or float
        if (sizeof(IO_t) == 1)
        {
            result = (result*scale + 128*bias[j]*scale)/(128*1024);
        }
        else
        {
            result = result + bias[j];
        }

        output_buffer[j] = result;
    }
}
    


template<   unsigned int in_features, unsigned int out_features, 
            class IO_t, class WEIGHT_t, class ACC_t, int io_max, int scale>
void Linear(IO_t *output_buffer, IO_t *input_buffer, const WEIGHT_t *weights, const WEIGHT_t *bias)
{ 
    ACC_t *output_buffer_acc = (ACC_t*)output_buffer;

    LinearACC<in_features, out_features, IO_t, WEIGHT_t, ACC_t, scale>(output_buffer_acc, input_buffer, weights, bias);
    
    for (unsigned int j = 0; j < out_features; j++)
    {
        auto result = output_buffer_acc[j];
        
        if (io_max != 0) 
        {
            if (result > io_max) 
                result = io_max;
                    
            if (result < -io_max)
                result = -io_max;
        }  

        output_buffer[j] = result; 
    }

}

#endif