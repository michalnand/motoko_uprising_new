import torch
import torch.nn as nn
import numpy


class Create(torch.nn.Module):

    def __init__(self, input_shape, output_shape):
        super(Create, self).__init__()

        self.device = torch.device("cuda" if torch.cuda.is_available() else "cpu")

        fc_size = (input_shape[1]//2)*(input_shape[2]//2)

        self.layers = [ 
                        nn.Conv2d(input_shape[0], 4, kernel_size = 3, stride = 2, padding = 1),
                        nn.ReLU(),  

                        nn.Conv2d(4, 8, kernel_size = 3, stride = 1, padding = 1),
                        nn.ReLU(),  

                        nn.Flatten(),
                        nn.Linear(fc_size*8, output_shape[0])
        ]
     
        for i in range(len(self.layers)):
            if hasattr(self.layers[i], "weight"):
                torch.nn.init.orthogonal_(self.layers[i].weight, 2**0.5)

        self.model = nn.Sequential(*self.layers)
        self.model.to(self.device)

        print(self.model)

    def forward(self, x):
        y = self.model.forward(x)
        return y
    
    def save(self, path):
        name = path + "model.pt"
        print("saving", name)
        torch.save(self.model.state_dict(), name) 

    def load(self, path):
        name = path + "model.pt"
        print("loading", name)

        self.model.load_state_dict(torch.load(name, map_location = self.device))
        self.model.eval() 

  