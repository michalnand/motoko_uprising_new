import torch
import torch.nn as nn

class Model(torch.nn.Module):
    def __init__(self, input_shape, outputs_count, hidden_size = 128):
        super(Model, self).__init__()

        self.device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
                
        self.model_features = nn.GRU(input_size=input_shape[1], hidden_size=hidden_size, batch_first=True)
            
        self.layers_output = [
            nn.Linear(hidden_size + outputs_count, hidden_size),
            nn.ReLU(),                       
            nn.Linear(hidden_size, outputs_count)
        ] 

        torch.nn.init.xavier_uniform_(self.layers_output[0].weight)
        torch.nn.init.uniform_(self.layers_output[2].weight, -0.003, 0.003)

        self.model_features.to(self.device)

        self.model_output = nn.Sequential(*self.layers_output)
        self.model_output.to(self.device)

        print("model_critic")
        print(self.model_features)
        print(self.model_output)
        print("\n\n")
       

    def forward(self, state, action):
        output, hn  = self.model_features(state)
        features = torch.cat([hn[0], action], dim=1)
        return self.model_output(features) 

    def save(self, path):
        print("saving to ", path)
        torch.save(self.model_features.state_dict(), path + "model_critic_features.pt")
        torch.save(self.model_output.state_dict(), path + "model_critic_output.pt")
       
    def load(self, path):       
        print("loading from ", path)
        self.model_features.load_state_dict(torch.load(path + "model_critic_features.pt", map_location = self.device))
        self.model_output.load_state_dict(torch.load(path + "model_critic_output.pt", map_location = self.device))
       
        self.model_features.eval()  
        self.model_output.eval()  
       


