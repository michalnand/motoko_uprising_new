#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <iostream>
#include <vector>

#include <LinePredictionModel.h>

namespace py = pybind11;

class ModelInterfacePython
{
    public:
        ModelInterfacePython()
        {
            std::cout << "ModelInterfacePython init done\n";
        }

        std::vector<float> forward(std::vector<float> &x)
        { 
            auto sequence_length = model.input_channels;
            auto inputs_count    = model.input_width;
            auto outputs_count   = model.output_height;

            std::vector<float> result(sequence_length*outputs_count);

            model.reset();

            for (unsigned int t = 0; t < sequence_length; t++)
            {
                for (unsigned int i = 0; i < inputs_count; i++)
                    model.input_buffer()[i] = x[t*inputs_count + i];

                model.forward();

                for (unsigned int i = 0; i < outputs_count; i++)
                    result[t*outputs_count + i] = model.output_buffer()[i];
            }
            
            return result;
        } 

    private:
        LinePredictionModel model;
};




PYBIND11_PLUGIN(LibEmbeddedNetwork)
{
    py::module mod("LibEmbeddedNetwork");

    py::class_<ModelInterfacePython>(mod, "ModelInterfacePython")
        .def(py::init<>())
        .def("forward", &ModelInterfacePython::forward);

    return mod.ptr();
}
