import sys
sys.path.insert(0,'../../../../')

import libs
import libs_dataset

import model   as ModelReference
import model_testing_float  as ModelTestingFloat


dataset = libs_dataset.DatasetLineFollowerStream()

libs.ExportTest(dataset, 64, ModelReference, ModelTestingFloat)
