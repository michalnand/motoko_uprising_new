import torch
import torch.nn as nn

class NoisyLinearFull(torch.nn.Module):
    def __init__(self, in_features, out_features, sigma = 1.0):
        super(NoisyLinearFull, self).__init__()
        
        self.out_features   = out_features
        self.in_features    = in_features
        self.sigma          = sigma

        self.weight  = nn.Parameter(torch.zeros(in_features, out_features))
        torch.nn.init.xavier_uniform_(self.weight)
        self.bias  = nn.Parameter(torch.zeros(out_features))
 

        self.weight_noise  = nn.Parameter(torch.zeros(in_features, out_features))
        torch.nn.init.xavier_uniform_(self.weight_noise)

        self.bias_noise  = nn.Parameter((0.1/out_features)*torch.randn(out_features)) 
 

    def forward(self, x): 
        noise           = self.sigma*torch.randn((self.in_features, self.out_features)).to(x.device).detach()
        bias_noise      = self.sigma*torch.randn((self.out_features)).to(x.device).detach()

        weight_noised   = self.weight + self.weight_noise*noise
        bias_noised     = self.bias   + self.bias_noise*bias_noise 

        return x.matmul(weight_noised) + bias_noised

    def __repr__(self):
        return "NoisyLinearFull(in_features={}, out_features={}, sigma={})".format(self.in_features, self.out_features, self.sigma)


class Model(torch.nn.Module):
    def __init__(self, input_shape, outputs_count, hidden_size = 128):
        super(Model, self).__init__()

        #self.device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
        self.device = "cpu"
                            
        self.layers = [
            nn.Flatten(),
            nn.Linear(input_shape[0]*input_shape[1], hidden_size),
            nn.ReLU(),
            NoisyLinearFull(hidden_size, hidden_size//2), 
            nn.ReLU(),                       
            NoisyLinearFull(hidden_size//2, outputs_count),
            nn.Tanh()  
        ] 

        torch.nn.init.xavier_uniform_(self.layers[1].weight)
        torch.nn.init.xavier_uniform_(self.layers[3].weight)
        torch.nn.init.uniform_(self.layers[5].weight, -0.3, 0.3)

        self.model = nn.Sequential(*self.layers)
        self.model.to(self.device)

        print("model_actor")
        print(self.model)
        print("\n\n")
       

    def forward(self, state):
        return self.model(state)

    def save(self, path):
        print("saving to ", path)
        torch.save(self.model.state_dict(), path + "model_actor.pt")
       
    def load(self, path):       
        print("loading from ", path)
        self.model.load_state_dict(torch.load(path + "model_actor.pt", map_location = self.device))
       
        self.model.eval()  
       