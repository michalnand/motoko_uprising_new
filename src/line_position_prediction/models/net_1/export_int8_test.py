import sys
sys.path.insert(0,'../../../../')

import libs
import libs_dataset

import model   as ModelReference
import model_testing_int8  as ModelTestingInt8


dataset = libs_dataset.DatasetLineFollowerStream()

libs.ExportTest(dataset, 64, ModelReference, ModelTestingInt8)
