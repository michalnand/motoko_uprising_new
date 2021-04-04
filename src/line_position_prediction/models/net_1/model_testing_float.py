import torch
import torch.nn as nn

import numpy

import export_float.LibEmbeddedNetwork

class Create(torch.nn.Module):

    def __init__(self, input_shape, output_shape):
        super(Create, self).__init__()
        self.model = export_float.LibEmbeddedNetwork.ModelInterfacePython()
        
    def forward(self, x):
        batch_size  = x.shape[0]
        seq_length  = x.shape[1]
        in_features = x.shape[2]
        
        classes_count = 3

        y    = torch.zeros((batch_size, seq_length, classes_count))

        for b in range(batch_size):
            x_np = x[b].detach().to("cpu").float().numpy()
            y_np = self.model.forward(x_np.flatten())
            y_np = numpy.reshape(y_np, (seq_length, classes_count))
            y[b] = torch.from_numpy(y_np).float()

        return y 
    
    def save(self, path):
        pass

    def load(self, path):
        pass
