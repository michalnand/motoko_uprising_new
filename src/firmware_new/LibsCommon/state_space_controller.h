#ifndef _LinearQuadraticControllerHidden_H_
#define _LinearQuadraticControllerHidden_H_

template<class DType, unsigned int required_dim, unsigned int plant_output_dim, unsigned int plant_input_dim, unsigned int hidden_dim, unsigned int scaling_nom = 1, unsigned int scaling_denom = 1> 
class LinearQuadraticControllerHidden
{
    public:
        void init(DType *controll_mat)
        {
            this->controll_mat = controll_mat;
        }

        void forward(DType *output, DType *required_state, DType *plant_state, DType *hidden_state)
        {
            //concatenate vectors
            //x = [required_state, plant_state, hidden_state]

            DType x[required_dim + plant_output_dim + hidden_dim];
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

            for (unsigned int i = 0; i < hidden_dim; i++)
            {
                x[ptr] = hidden_state[i];
                ptr++;
            }
            

            //hidden_new, plant_u = matmul(x, controll_mat)

            //hidden state update
            ptr = 0;
            for (unsigned int j = 0; j < hidden_dim; j++)
            {
                DType sum = 0;

                for (unsigned int i = 0; i < (required_dim + plant_output_dim + hidden_dim); i++)
                {
                    sum+= x[i]*controll_mat[ptr];
                    ptr++;
                } 
                
                hidden_state[j] = (sum*scaling_nom)/scaling_denom;
            }

            //plant controll input update
            for (unsigned int j = 0; j < plant_input_dim; j++)
            {
                DType sum = 0;

                for (unsigned int i = 0; i < (required_dim + plant_output_dim + hidden_dim); i++)
                {
                    sum+= x[i]*controll_mat[ptr];
                    ptr++;
                } 
                
                output[j] = (sum*scaling_nom)/scaling_denom;
            }
        }

    private:
        DType *controll_mat;
};

#endif