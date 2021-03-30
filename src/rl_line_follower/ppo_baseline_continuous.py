import gym
import gym_line_follower

import numpy
import time

import RLAgents

import models.ppo_baseline_continuous.src.model            as Model
import models.ppo_baseline_continuous.src.config           as Config


path = "models/ppo_baseline_continuous/"

config  = Config.Config()

envs = RLAgents.MultiEnvSeq('LineFollower-v0', None, config.actors)

agent = RLAgents.AgentPPOContinuous(envs, Model, Config) 

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