import numpy
import matplotlib.pyplot as plt
import json

class LineModel:
    def __init__(self, file_name_prefix):
      

        json_file   = open(file_name_prefix + ".json")
        json_data   = json.load(json_file)
        json_file.close()

        self.points  = numpy.array(list(json_data["points"]))
        self.visited = numpy.zeros(self.get_length(), dtype=bool)

    def get_length(self):
        return self.points.shape[0]

    def set_visited(self, idx):
        if self.visited[idx] == False:
            self.visited[idx] = True
            return True
        else:
            return False

    def get_closest(self, x, y):
        position = [x, y]

        dif         = self.points - position
        distances   = (numpy.sum((dif**2), axis = 1))**0.5

        closest_idx         = numpy.argmin(distances)
        closest_distance    = distances[closest_idx]

        return closest_idx, closest_distance

    def get_start(self, idx):
        dx = self.points[idx + 1][0] - self.points[idx][0]
        dy = self.points[idx + 1][1] - self.points[idx][1]

        yaw = numpy.arctan2(dy, dx)

        point       = [self.points[idx][0], self.points[idx][1], 0.05]
        orientation = [yaw, 0.0, 0.0]
        return [point, orientation]

    def get_start_random(self):
        idx = (numpy.random.randint(50)+10)%self.get_length()
        return self.get_start(idx)
