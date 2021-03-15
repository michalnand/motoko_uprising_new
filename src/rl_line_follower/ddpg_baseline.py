import gym
import gym_line_follower

import numpy
import time

import RLAgents


import models.ddpg_baseline.src.model_critic     as ModelCritic
import models.ddpg_baseline.src.model_actor      as ModelActor
import models.ddpg_baseline.src.config           as Config

path = "models/ddpg_baseline/"

env = gym.make("LineFollower-v0")

agent = RLAgents.AgentDDPG(env, ModelCritic, ModelActor, Config)


max_iterations = 4*(10**6)
trainig = RLAgents.TrainingIterations(env, agent, max_iterations, path, 1000)
trainig.run()

'''
agent.load(path)
agent.disable_training()

while True:
    agent.main()
    env.render()
'''