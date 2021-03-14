import torch
import torch.nn as nn

class Model(torch.nn.Module):

    def __init__(self, input_shape, outputs_count):
        super(Model, self).__init__()

        #self.device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
        self.device = "cpu"
        
        hidden_size = 128
        
        self.model_features = nn.GRU(input_size=input_shape[1], hidden_size=hidden_size, batch_first=True)
            
        self.layers_mu = [
            nn.Linear(hidden_size, hidden_size//2),
            nn.ReLU(),                       
            nn.Linear(hidden_size//2, outputs_count),
            nn.Tanh()
        ]  

        self.layers_var = [
            nn.Linear(hidden_size, hidden_size//2),
            nn.ReLU(),                       
            nn.Linear(hidden_size//2, outputs_count),
            nn.Softplus()
        ]  

        self.layers_value = [
            nn.Linear(hidden_size, hidden_size//2),
            nn.ReLU(),                      
            nn.Linear(hidden_size//2, 1)
        ]

        torch.nn.init.xavier_uniform_(self.layers_mu[0].weight)
        torch.nn.init.xavier_uniform_(self.layers_mu[2].weight)

        torch.nn.init.xavier_uniform_(self.layers_var[0].weight)
        torch.nn.init.xavier_uniform_(self.layers_var[2].weight)

        torch.nn.init.xavier_uniform_(self.layers_value[0].weight)
        torch.nn.init.xavier_uniform_(self.layers_value[2].weight)


        self.model_features.to(self.device)

        self.model_mu = nn.Sequential(*self.layers_mu)
        self.model_mu.to(self.device)

        self.model_var = nn.Sequential(*self.layers_var)
        self.model_var.to(self.device)

        self.model_value = nn.Sequential(*self.layers_value)
        self.model_value.to(self.device)

        
        print("model_ppo")
        print(self.model_features)
        print(self.model_mu)
        print(self.model_var)
        print(self.model_value)
        print("\n\n")


    def forward(self, state):
        output, hn    = self.model_features(state)
        features = hn[0]

        mu      = self.model_mu(features)
        var     = self.model_var(features)
        value   = self.model_value(features)
        
        return mu, var, value

    def save(self, path):
        print("saving to ", path)
        torch.save(self.model_features.state_dict(), path + "model_features.pt")
        torch.save(self.model_mu.state_dict(), path + "model_mu.pt")
        torch.save(self.model_var.state_dict(), path + "model_var.pt")
        torch.save(self.model_value.state_dict(), path + "model_value.pt")

    def load(self, path):       
        print("loading from ", path)
        self.model_features.load_state_dict(torch.load(path + "model_features.pt", map_location = self.device))
        self.model_mu.load_state_dict(torch.load(path + "model_mu.pt", map_location = self.device))
        self.model_var.load_state_dict(torch.load(path + "model_var.pt", map_location = self.device))
        self.model_value.load_state_dict(torch.load(path + "model_value.pt", map_location = self.device))

        self.model_features.eval()  
        self.model_mu.eval()  
        self.model_var.eval()  
        self.model_value.eval()  
    
