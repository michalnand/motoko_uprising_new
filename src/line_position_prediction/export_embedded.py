import sys
sys.path.insert(0,'../..')

import libs

'''
input_shape     = (1, 8, 8)
output_shape    = (5, )


model_path = "./models/net_0/"
import models.net_0.model as Net0

model = Net0.Create(input_shape, output_shape)
model.load(model_path + "trained/")

export = libs.ExportNetwork(model, input_shape, export_path = model_path + "/export/", network_prefix = "LineNetwork")


model_path = "./models/net_1/"
import models.net_1.model as Net1

model = Net1.Create(input_shape, output_shape)
model.load(model_path + "trained/")

export = libs.ExportNetwork(model, input_shape, export_path = model_path + "/export/", network_prefix = "LineNetwork")
'''


input_shape     = (1, 64, 64)
output_shape    = (5, )


model_path = "./models/net_2/"
import models.net_2.model as Net2

model = Net2.Create(input_shape, output_shape)
model.load(model_path + "trained/")

export = libs.ExportNetwork(model, input_shape, export_path = model_path + "/export/", network_prefix = "LineNetwork")
