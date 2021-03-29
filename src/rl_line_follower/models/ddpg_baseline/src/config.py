import RLAgents

class Config():

    def __init__(self):        
        self.gamma                  = 0.95
        self.critic_learning_rate   = 0.0002
        self.actor_learning_rate    = 0.0001
        self.tau                    = 0.001

        self.batch_size          = 64
        self.update_frequency    = 4

        self.exploration   = RLAgents.DecayConst(0.1, 0.1)

        self.experience_replay_size = 200000
