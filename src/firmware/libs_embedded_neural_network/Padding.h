#ifndef _Padding_H_
#define _Padding_H_

#include <stdint.h>

template<class DType, unsigned int channels, unsigned int height, unsigned int width, unsigned int padding>
void Padding( DType *output_buffer, DType *input_buffer)
{
    for (unsigned int i = 0; i < channels*(height+2*padding)*(width+2*padding); i++)
        output_buffer[i] = 0;

    for (unsigned int h = 0; h < height; h++)
        for (unsigned int w = 0; w < width; w++)
            for (unsigned int ch = 0; ch < channels; ch++)
            {
                output_buffer[((h + padding)*width + w + padding)*channels + ch] = input_buffer[(h*width + w)*channels + ch]; 
            }
}

#endif