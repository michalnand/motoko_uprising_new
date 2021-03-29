import torch
import torch.nn as nn

class Model(torch.nn.Module):
    def __init__(self, input_shape, outputs_count, hidden_size = 128):
        super(Model, self).__init__()

        #self.device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
        self.device = "cpu"
                
        self.layers = [
            nn.Linear(input_shape[0]*input_shape[1] + outputs_count, hidden_size),
            nn.Linear(),
            nn.Linear(hidden_size, hidden_size//2),
            nn.ReLU(),                       
            nn.Linear(hidden_size//2, outputs_count) 
        ] 

        torch.nn.init.xavier_uniform_(self.layers[0].weight)
        torch.nn.init.xavier_uniform_(self.layers[2].weight)
        torch.nn.init.uniform_(self.layers[4].weight, -0.003, 0.003)

        self.model = nn.Sequential(*self.layers)
        self.model.to(self.device)

        print("model_critic")
        print(self.model)
        print("\n\n")
       

    def forward(self, state, action):
        x = torch.cat([state.view(state.shape[0], -1), action], dim=1)
        return self.model(x) 

    def save(self, path):
        print("saving to ", path)
        torch.save(self.model.state_dict(), path + "model_critic.pt")
       
    def load(self, path):       
        print("loading from ", path)
        self.model.load_state_dict(torch.load(path + "model_critic.pt", map_location = self.device))       
        self.model.eval()  
       


