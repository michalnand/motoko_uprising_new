from gym.envs.registration import register

register(
    id='LineFollower-v0',
    entry_point='gym_line_follower.envs:LineFollowerEnv'
)
