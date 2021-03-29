import gym
import gym_line_follower
import time
import numpy

env = gym.make("LineFollower-v0")

state = env.reset()

left  = 0.0
right = 0.0

speed_max = 0.5

speed = 0.0
acceleration = 0.002

step = 0

score = 0.0

while True:

    time_start = time.time()

    x0 = state[-1][0]
    x1 = state[-2][0]
    dif   = 0.1*x0 + 0.1*(x0 - x1)
    left  = numpy.clip(dif + speed, 0.0, speed_max)
    right = numpy.clip(-dif + speed, 0.0, speed_max)

    speed = (1.0 - acceleration)*speed + acceleration*0.3
    
    if step%10 == 0:
        env.render()

    state, reward, done, _ = env.step([left, right])
    
    score+= reward

    print("score = ", score)
    
    if done:
        score = 0.0
        speed = 0.0
        env.reset()
       

    time_stop = time.time()

    step+= 1
