#ifndef _MATRIX_VECTOR_H_
#define _MATRIX_VECTOR_H_

#define LINEAR_TILE_ROWS    ((unsigned int)8)
#define LINEAR_TILE_COLS    ((unsigned int)4)

template<   unsigned int in_features, unsigned int out_features, 
            class IO_t, class WEIGHT_t, class ACC_t, int io_max, int scale>
void Linear(IO_t *output_buffer, IO_t *input_buffer, const WEIGHT_t *weights, const WEIGHT_t *bias)
{ 
    for (unsigned int j = 0; j < out_features; j++)
    {
        output_buffer[j] = 0;
    }

    //naive code
    //cache disabled, clock 216MHz, speed 12.1Mops/s
    //cache enabled, clock 216MHz, speed 58Mops/s
    
    /*
    for (unsigned int i = 0; i < in_features; i++)
    {
        for (unsigned int j = 0; j < out_features; j++)
        {
            output_buffer[j]+= weights[j*in_features + i]*input_buffer[i]; 
        }
    }
    */

    //tiling to size 8x4
    //cache disabled, clock 216MHz, speed 21.1Mops/s
    //cache enabled, clock 216MHz, speed 120Mops/s
    for (unsigned int i = 0; i < in_features; i+= LINEAR_TILE_COLS)
    { 
        for (unsigned int j = 0; j < out_features; j+= LINEAR_TILE_ROWS)
        {
            for (unsigned int jj = 0; jj < LINEAR_TILE_ROWS; jj++)
                for (unsigned int ii = 0; ii < LINEAR_TILE_COLS; ii++)
                    output_buffer[j + jj]+= weights[(j + jj)*in_features + i + ii]*input_buffer[i + ii]; 
        }
    }


    if (typeid(IO_t) == typeid(float))
    {
        output_buffer = (output_buffer*scale)/1024;
    }
    else 
    {
        output_buffer = (output_buffer*scale)/(128*1024);
    }

    output_buffer = output_buffer + (bias[j]*scale)/1024;

    if (io_max != 0) 
    {
        if (output_buffer > io_max) 
            output_buffer = io_max;
                
        if (output_buffer < -io_max)
            output_buffer = -io_max;
    }  
}

#endif