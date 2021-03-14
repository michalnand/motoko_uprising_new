class Config(): 
    def __init__(self):
        self.gamma                  = 0.99
        self.entropy_beta           = 0.001
        self.eps_clip               = 0.2

        self.steps                  = 128
        self.batch_size             = 16
        
        self.training_epochs        = 4
        self.actors                 = 16
        
        self.learning_rate          = 0.00025
