import gym
import gym_line_follower
import time
import numpy

env = gym.make("LineFollower-v0")

state = env.reset()


target_left = 1.0
target_right = 1.0

left  = 0.0
right = 0.0

speed_max = 0.5

acc = 0.02

fps = 0.0
k = 0.05

step = 0
while True:
    dif   = 0.1*state[-1][0] + 0.1*(state[-1][0] - state[-2][0])
    left  = numpy.clip(dif + acc, 0.0, speed_max)
    right = numpy.clip(-dif + acc, 0.0, speed_max)
    
    if step%10 == 0:
        env.render()
    step+= 1

    time_start = time.time()
    state, reward, done, _ = env.step([left, right])
    time_stop = time.time()

    fps = (1.0 - k)*fps + k/(time_stop - time_start)

    print(step, reward, done)
    
    if done:
        env.reset()
        left  = 0.0
        right = 0.0


    time.sleep(0.01)
