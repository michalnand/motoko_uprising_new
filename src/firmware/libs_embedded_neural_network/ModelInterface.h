#ifndef _MODEL_INTERFACE_H_
#define _MODEL_INTERFACE_H_

#include <stdint.h>

#include "Linear.h"


#include "Conv1d.h"
#include "Conv2d.h"
#include "GRU.h"
#include "ReLU.h"
#include "GlobalAveragePool.h"
#include "ChannelReorder.h"

template<class DType>
class ModelInterface
{
    public:
        ModelInterface()
        {
            buffer_a = nullptr;
            buffer_b = nullptr;
        }

        virtual ~ModelInterface()
        {
            delete buffer_a;
            delete buffer_b;
        }

        virtual void forward()
        {

        }

    public:
        DType* input_buffer()
        {
            if (!swapped)
                return buffer_a; 
            else
                return buffer_b;
        }

        DType* output_buffer()
        {
            if (!swapped)
                return buffer_b;
            else
                return buffer_a;
        }

    public:
        unsigned int input_channels, input_height, input_width;
        unsigned int output_channels, output_height, output_width;
        unsigned int total_macs;

    protected:
        void init_buffer(unsigned int size)
        {
            swapped  = false;
  
            buffer_a = new DType[size];
            buffer_b = new DType[size];

            for (unsigned int i = 0; i < size; i++)
                buffer_a[i] = 0;

            for (unsigned int i = 0; i < size; i++)
                buffer_b[i] = 0;
        }

        void swap_buffer()
        {
            swapped = !swapped;
        }

    protected:
        bool swapped;
        DType *buffer_a, *buffer_b;
};


#endif

