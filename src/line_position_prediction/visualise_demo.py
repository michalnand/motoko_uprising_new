import sys
sys.path.append("..")
import time
import numpy
import torch
import opengl_gui
import dataset_line_follower_stream
import models.net_1.model as Model

gui     = opengl_gui.GLGui("./resources/gui.json")


points_count    = 512

line_points     = dataset_line_follower_stream.LinePoints(points_count)

dataset_line    = line_points.points
dataset_sensors = line_points.sensors
dataset_labels  = line_points.labels

model           = Model.Create((line_points, 8), (line_points, 3))
model.load("models/net_1/trained/")

model_input         = torch.from_numpy(dataset_sensors).to(model.device).unsqueeze(0).float()
model_prediction    = model.forward(model_input).squeeze(0).detach().to("cpu").numpy()


value_idx = 0

while gui.main_step() != True:
    ground_truth = numpy.argmax(dataset_labels[value_idx])
    prediction   = numpy.argmax(model_prediction[value_idx])


    gui.variables.add("ground_truth_image",     ground_truth + 100)

    if ground_truth == prediction:
        gui.variables.add("prediction_image", prediction   + 100)
    else:
        gui.variables.add("prediction_image", prediction   + 103)
    

    gui.variables.add("line_sensors", dataset_sensors[value_idx])
    gui.variables.add("line_position", [value_idx, dataset_line[0], dataset_line[1]])

    value_idx = (value_idx + 4)%points_count

    #time.sleep(0.1)
