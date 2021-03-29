#ifndef _GlobalAveragePool_H_
#define _GlobalAveragePool_H_

#include <stdint.h>


template<   unsigned int height, unsigned int width, unsigned int channels,
            class IO_t, class ACC_t, int io_max>
void GlobalAveragePool(IO_t *output_buffer, IO_t *input_buffer)
{
    unsigned int size = height*width;

    ACC_t result[channels];
    for (unsigned int i = 0; i < channels; i++)
        result[i] = 0;

    for (unsigned int j = 0; j < size; j++)
    {
        for (unsigned int i = 0; i < channels; i++)
            result[i]+= input_buffer[i];
        
        input_buffer+= channels; 
    }

    for (unsigned int i = 0; i < channels; i++)
    {
        ACC_t tmp = result[i]/size;

        if (io_max != 0)
        {
            if (tmp > io_max)
                tmp = io_max;

            if (tmp < -io_max)
                tmp = -io_max;
        }

        output_buffer[i] = tmp;
    }
}


#endif