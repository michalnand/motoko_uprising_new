import numpy
import cv2
import os
import time
import gym

from .PybulletClient    import *
from .LineModel         import *
from .LineFollowerBot   import *

from shapely.geometry import Point
from shapely.geometry.polygon import Polygon

class Config:
    def __init__(self):
        #common environment parameters
        self.dt                 = 0.005     #200Hz, sampling
        self.gravity            = -9.81     #9.81m/s^2

        self.max_episode_steps  = 16384  #max steps

        #line parameters
        self.line_base_points   = 16
        self.line_width         = 0.015     #15mm
        self.line_files_count   = 64


        #robot parameters
        self.robot_sensors_brace    = 0.035
        self.supply_voltage         = 8         #8Volts main battery

        self.nominal_voltage        = 6         #6Volts motors
        self.no_load_speed          = 1000      #1000rpm
        self.stall_torque           = 0.57      #0.57kg.cm, converted into Nm

        self.sequence_length        = 64 
        
        '''
        self.no_load_speed     = rnd(500, 1500)
        self.inertia           = rnd(0.6, 0.95)
        self.wheels_brace      = rnd(0.04, 0.2)
        self.sensors_distance  = rnd(0.04, 0.2)
        '''



    def rnd(min_value, max_value):
        k = numpy.random.rand()
        return (1.0 - k)*min_value + k*max_value


 
class LineFollowerEnv(gym.Env):
    def __init__(self, Config = Config):
        gym.Env.__init__(self)

        self.config     = Config()

        self.pb_client  = PybulletClient()
        self.path       = os.path.dirname(os.path.abspath(__file__))

        self.action_space       = gym.spaces.Box(low=-1.0, high=1.0, shape=(2,), dtype=numpy.float32)
        self.observation_space  = gym.spaces.Box(low=-1.0, high=1.0, shape=(self.config.sequence_length, 4), dtype=numpy.float32)

        self.reset()

    def reset(self):
        self.path_file_name_prefix = self.path + "/models/lines/" + str(numpy.random.randint(self.config.line_files_count))

        self.pb_client.resetSimulation()
        self.pb_client.setTimeStep(1.0/200.0)

        self.base_plane_model     = self.pb_client.loadURDF(self.path + "/models/base.urdf")
 
        self.line_model     = LineModel(self.path_file_name_prefix)
        self.line_polygon   = Polygon(self.line_model.points)
 
        self.new_line_model = True

     
        starting_position   = self.line_model.get_start_random()
        self.robot_model    = LineFollowerBot(self.pb_client, self.path + "/models/robot_motoko.urdf", self.config, starting_position)

        self.pb_client.setGravity(0, 0, self.config.gravity)
        self.pb_client.setTimeStep(self.config.dt)

        for i in range(100):
            self.pb_client.stepSimulation()

        self.observation = numpy.zeros((self.config.sequence_length, 4))
        self._update_observation()

        self.iterations = 0 
        #self.line_model.show()

        return self.observation


    def step(self, action):
        self.iterations+= 1

        self.robot_model.set_throttle(action[0], action[1])
        self.pb_client.stepSimulation()

        closest_idx, line_pos_raw = self._get_line_position()

        line_position = numpy.clip(line_pos_raw, -self.config.robot_sensors_brace, self.config.robot_sensors_brace)/self.config.robot_sensors_brace

        reward = 0.0
        done   = False

        reward = (1.0 - numpy.abs(line_position))*0.001

        if numpy.abs(line_pos_raw) > 3.0*self.config.robot_sensors_brace:
            done = True
            reward = -1.0
        elif numpy.abs(line_pos_raw) > self.config.robot_sensors_brace:
            reward = -0.1
        elif self.line_model.set_visited(closest_idx) == True:
            reward+= 1.0

        if self.iterations >= self.config.self.max_episode_steps:
            done = True

        self._update_observation()

        return self.observation, reward, done, None

    def render(self):

        if self.new_line_model:
            self.line_model_pb      = self.pb_client.loadURDF(self.path_file_name_prefix + ".urdf")
            self.new_line_model     = False


        width  = 256
        height = 256

        robot_x, robot_y, robot_z, pitch, roll, yaw = self.robot_model.get_position()

        #top view
        top_view = self.robot_model.get_image(yaw*180.0/numpy.pi - 90, -90.0, 0.0, 0.25, robot_x, robot_y, robot_z, width = width, height = height)

        #third person view
        dist = 0.02
        tp_view = self.robot_model.get_image(yaw*180.0/numpy.pi - 90, -40.0, 0.0, 0.1, robot_x+dist*numpy.cos(yaw), robot_y+dist*numpy.sin(yaw), robot_z, width = width, height = height, fov=100)

        #camera view
        cam_view = self._get_camera_view(width=width, height=height)

        #sensor view
        #dist = 0.05
        #sensor_view = self.robot_model.get_image(yaw*180.0/numpy.pi - 90, -90.0, 0.0, 0.02, robot_x+dist*numpy.cos(yaw), robot_y+dist*numpy.sin(yaw), robot_z + 0.02, width = width, height = height, fov=100)

        #side view
        dist = 0.02
        side_view = self.robot_model.get_image(yaw*180.0/numpy.pi - 0, -40.0, 0.0, 0.1, robot_x+dist*numpy.cos(yaw), robot_y+dist*numpy.sin(yaw), robot_z, width = width, height = height, fov=100)

        separator_width = 4
        vertical_separator   = 0.5*numpy.ones((height, separator_width, 3))
        horizontal_separator = 0.5*numpy.ones((separator_width, width*2 + separator_width, 3))

        image_a = numpy.hstack([ numpy.hstack([top_view, vertical_separator]), tp_view])
        image_b = numpy.hstack([ numpy.hstack([cam_view, vertical_separator]), side_view])

        image = numpy.vstack([numpy.vstack([image_a, horizontal_separator]), image_b] )
        image = numpy.clip(255*image, 0.0, 255.0)

        image = numpy.array(image, dtype=numpy.uint8)

        self._draw_fig(image)

        print("time = ", round(self.robot_model.time, 3), " [s]") 
        print("v wheel [left, right] = ", round(self.robot_model.left_velocity, 3), round(self.robot_model.right_velocity, 3))
        v, aw = self.robot_model.pb_client.getBaseVelocity(self.robot_model.bot_model)
        print("v base [x, y, z] = ", numpy.round(v, 3), " [m/s]")

        
        print("\n\n")
        

    def _draw_fig(self, image):
        rgb = cv2.cvtColor(image,cv2.COLOR_BGR2RGB)
        cv2.imshow("line follower", rgb)  
        cv2.waitKey(1)

    def _get_camera_view(self, width = 256, height = 256):
        robot_x, robot_y, robot_z, pitch, roll, yaw = self.robot_model.get_position()
        r  = 0.15
        cam_dx = r*numpy.cos(yaw)
        cam_dy = r*numpy.sin(yaw)
        return self.robot_model.get_image(yaw*180.0/numpy.pi - 90, -60.0, 0.0, 0.025, robot_x + cam_dx, robot_y + cam_dy, robot_z + 0.04, width = width, height = height, fov=120)
    
    
    def _get_line_position(self, sensor_distance = 0.04):

        x, y, _, _, _, yaw = self.robot_model.get_position()
        x_ = x + sensor_distance*numpy.cos(yaw)
        y_ = y + sensor_distance*numpy.sin(yaw) 

        closest_idx, distance  = self.line_model.get_closest(x_, y_)

        if self.line_polygon.contains(Point(x_, y_)):
            line_position = 1.0*distance
        else:
            line_position = -1.0*distance

        return closest_idx, line_position

    def _update_observation(self):
        frames = self.observation.shape[0]

        self.observation =  numpy.roll(self.observation,-1,0)
            
        _, line_pos_raw = self._get_line_position()
        velocity_left, velocity_right = self.robot_model.get_wheel_velocity()

        self.observation[-1][0] = numpy.clip(line_pos_raw, -self.config.robot_sensors_brace, self.config.robot_sensors_brace)/self.config.robot_sensors_brace
        self.observation[-1][1] = velocity_left/self.config.no_load_speed
        self.observation[-1][2] = velocity_right/self.config.no_load_speed
        
        if numpy.abs(line_pos_raw) < self.config.robot_sensors_brace:
            self.observation[-1][3] = 1.0
        else:
            self.observation[-1][3] = 0.0




