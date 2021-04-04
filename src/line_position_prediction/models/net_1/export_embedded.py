import sys
sys.path.insert(0,'../../../..')

import embedded_inference.libs_embedded


input_shape     = (128, 8)
output_shape    = (128, 3)

import model

model_path      = "./"
pretrained_path = model_path + "trained/"


export_path     = model_path + "export_float/"
embedded_inference.libs_embedded.ExportModel("LinePredictionModel", input_shape, output_shape, model, pretrained_path, export_path, "float", True)

export_path     = model_path + "export_int8/"
embedded_inference.libs_embedded.ExportModel("LinePredictionModel", input_shape, output_shape, model, pretrained_path, export_path, "int8", True)
