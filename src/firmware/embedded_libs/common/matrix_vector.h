#ifndef _MATRIX_VECTOR_H_
#define _MATRIX_VECTOR_H_

#define MV_TILE_ROWS    ((unsigned int)8)
#define MV_TILE_COLS    ((unsigned int)4)

template<unsigned int inputs_count, unsigned int outputs_count, class ACC_t, class MATRIX_t, class VECTOR_t>
void matrix_vector(ACC_t *result_out, MATRIX_t *matrix_in, VECTOR_t *vector_in)
{ 
    //naive code
    //cache disabled, clock 216MHz, speed 12.1Mops/s
    //cache enabled, clock 216MHz, speed 58Mops/s
    
    /*
    for (unsigned int i = 0; i < inputs_count; i++)
    {
        for (unsigned int j = 0; j < outputs_count; j++)
        {
            result_out[j]+= matrix_in[j*inputs_count + i]*vector_in[i]; 
        }
    }
    */

    //tiling to size 8x4
    //cache disabled, clock 216MHz, speed 21.1Mops/s
    //cache enabled, clock 216MHz, speed 120Mops/s
    for (unsigned int i = 0; i < inputs_count; i+= MV_TILE_COLS)
    {
        for (unsigned int j = 0; j < outputs_count; j+= MV_TILE_ROWS)
        {
            for (unsigned int jj = 0; jj < MV_TILE_ROWS; jj++)
                for (unsigned int ii = 0; ii < MV_TILE_COLS; ii++)
                    result_out[j + jj]+= matrix_in[(j + jj)*inputs_count + i + ii]*vector_in[i + ii]; 
        }
    }
}

#endif