import gym
import gym_line_follower
import time
import numpy

env = gym.make("LineFollower-v0")


target_left = 1.0
target_right = 1.0

left  = 0.0
right = 0.0

speed_max = 0.7

acc = 0.02

fps = 0.0
k = 0.05

while True:
    left = numpy.clip(left + acc, 0.0, speed_max)
    right = numpy.clip(right + acc, 0.0, speed_max)
    
    env.render()

    time_start = time.time()
    state, reward, done, _ = env.step([left, right])
    time_stop = time.time()

    fps = (1.0 - k)*fps + k/(time_stop - time_start)

    print("fps = ", fps)
    print(state)
    print(reward)
    print(done)

    if done:
        env.reset()
        left  = 0.0
        right = 0.0


    time.sleep(0.01)
