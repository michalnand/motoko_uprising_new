import gym
import gym_line_follower

import numpy
import time

import RLAgents

import models.ppo_baseline_discrete.src.model            as Model
import models.ppo_baseline_discrete.src.config           as Config

class Wrapper(gym.Wrapper):
    def __init__(self, env):
        gym.Wrapper.__init__(self, env) 

        self.action_space       = gym.spaces.Discrete(16)

        actions = []
        actions.append([0.0, 0.0])
        actions.append([0.5, 0.5])
        actions.append([0.8, 0.8])
        actions.append([1.0, 1.0])

        actions.append([0.0, 0.2])
        actions.append([0.0, 0.4])
        actions.append([0.0, 0.8])
        actions.append([0.0, 1.0])

        actions.append([0.2, 0.0])
        actions.append([0.4, 0.0])
        actions.append([0.8, 0.0])
        actions.append([1.0, 0.0])

        actions.append([0.2, 1.0])
        actions.append([0.4, 0.8])
        actions.append([0.8, 0.4])
        actions.append([1.0, 0.2])

        self.actions = numpy.array(actions, dtype=numpy.float32)

    def step(self, action):
        act = self.actions[action]
        return self.env.step(act)

    def reset(self):
        return self.env.reset()



path = "models/ppo_baseline_discrete/"

config  = Config.Config()

envs = RLAgents.MultiEnvSeq('LineFollower-v0', Wrapper, config.actors)

agent = RLAgents.AgentPPO(envs, Model, Config) 

max_iterations = 1*(10**6) 

trainig = RLAgents.TrainingIterations(envs, agent, max_iterations, path, 1000)
trainig.run() 

'''
agent.load(path)
agent.disable_training()

while True:
    agent.main()
    envs.render(0)
'''