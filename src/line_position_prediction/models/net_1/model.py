import torch
import torch.nn as nn
import numpy


class Create(torch.nn.Module):

    def __init__(self, input_shape, output_shape):
        super(Create, self).__init__()

        self.device = torch.device("cuda" if torch.cuda.is_available() else "cpu")

        self.gru      = nn.GRU(input_size=input_shape[1], hidden_size=64, batch_first = True)
        self.linear   = nn.Linear(64, output_shape[1])

        self.gru.to(self.device)
        self.linear.to(self.device)

        print(self.gru)
        print(self.linear)

    def forward(self, x):
        gru_y, hn   = self.gru(x)
        y           = self.linear(gru_y)
        return y


    def save(self, path):
        torch.save(self.gru.state_dict(),    path + "model_gru.pt") 
        torch.save(self.linear.state_dict(), path + "model_linear.pt") 

    def load(self, path):
        self.gru.load_state_dict(torch.load(path + "model_gru.pt", map_location = self.device))
        self.linear.load_state_dict(torch.load(path + "model_linear.pt", map_location = self.device))

        self.gru.eval() 
        self.linear.eval()