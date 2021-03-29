#ifndef _ChannelReorder_H_
#define _ChannelReorder_H_

#include <stdint.h>

template<class DType, unsigned int channels, unsigned int height, unsigned int width>
void ChannelReorder( DType *output_buffer, DType *input_buffer)
{
    for (unsigned int ch = 0; ch < channels; ch++)
        for (unsigned int h = 0; h < height; h++)
            for (unsigned int w = 0; w < width; w++)
            {
                output_buffer[((ch*height + h)*width + w)] = input_buffer[(h*width + w)*channels + ch]; 
            }
}

#endif