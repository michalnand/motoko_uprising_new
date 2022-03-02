#ifndef _LinearQuadraticController_H_
#define _LinearQuadraticController_H_

template<class DType, unsigned int required_dim, unsigned int plant_output_dim, unsigned int plant_input_dim, unsigned int scaling_nom = 1, unsigned int scaling_denom = 1> 
class LinearQuadraticController
{
    public:
        LinearQuadraticController()
        {
            for (unsigned int i = 0; i < plant_input_dim*(required_dim + plant_output_dim); i++)
            {
                controll_mat[i] = 0;
            }
        }

        virtual ~LinearQuadraticController()
        {

        }

        void init(DType *controll_mat)
        {
            this->controll_mat = controll_mat;
        }

        void forward(DType *output, DType *required_state, DType *plant_state)
        {
            //concatenate vectors
            //x = [required_state, plant_state]
            unsigned int ptr = 0;
            
            for (unsigned int i = 0; i < required_dim; i++)
            {
                x[ptr] = required_state[i];
                ptr++;
            }

            for (unsigned int i = 0; i < plant_output_dim; i++)
            {
                x[ptr] = plant_state[i];
                ptr++;
            }

            //plant_u = matmul(x, controll_mat)
            mat_vect_mul<DType, plant_input_dim, required_dim + plant_output_dim>(output, this->controll_mat, x);

            for (unsigned int i = 0; i < plant_input_dim; i++)
            {
                output[i] = (output[i]*scaling_nom)/scaling_denom;
            }
        }

    private:
        DType x[required_dim + plant_output_dim];
        DType controll_mat[(required_dim + plant_output_dim)];
};

#endif