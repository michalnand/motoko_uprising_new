import numpy
import torch
import matplotlib.pyplot as plt

class LinePoints:
    def __init__(self, points_count = 10000, nominal_velocity = 1.0, minimum_radius = 0.05, sensors_brace = 0.08, sampling_frequency = 200, sensors_count = 8):
        d_pos_max       = nominal_velocity*1.0/sampling_frequency
        dx_max          = d_pos_max*(1.0 - minimum_radius)

        self.points     = numpy.zeros((points_count, 2), dtype=numpy.float32)

        y   = 0.0 
        x   = 0.0
        dx  = 0.0

        state = 0
        p_change = 0.025
        for i in range(points_count):
            self.points[i][0] = x
            self.points[i][1] = y

            if state == 0:
                dx = numpy.clip(0.0 - x, -dx_max, dx_max)
                if abs(x) < 0.05 and numpy.random.rand() < p_change:
                    state = numpy.random.randint(2) + 1
            elif state == 1: 
                dx = dx_max*numpy.random.rand()
                if x > 0.98 or numpy.random.rand() < p_change:
                    state = 0
            elif state == 2:
                dx = -dx_max*numpy.random.rand()
                if x < -0.98 or numpy.random.rand() < p_change:
                    state = 0

            x   = numpy.clip(x + dx, -0.5*sensors_brace, 0.5*sensors_brace)
            y   = y + (d_pos_max**2 - dx**2)**0.5

        self.points     = numpy.transpose(self.points)
        self.points[0]  = self.points[0]/(0.5*sensors_brace)

        self.sensors    = self._points_to_sensors_reading(self.points[0], sensors_count)
        self.labels     = self._points_to_labels(self.points[0])

        '''
        f, axarr = plt.subplots(1, 2)
        axarr[0].plot(self.points[0], self.points[1], color='deepskyblue')
        axarr[0].set_title("line position")
        axarr[0].margins(0,0)

        axarr[1].matshow(numpy.flip(self.sensors, 0), extent=[0,7,0,50])
        axarr[1].axes.get_yaxis().set_visible(False)
        axarr[1].set_title("sensors output")
        axarr[1].margins(0,0)
        
        plt.margins(0,0)
        plt.show()
        '''

    def _points_to_sensors_reading(self, points, sensors_count, filter_k = 15.0):

        weights_left  = -(1.0 - range(sensors_count//2)*numpy.ones(sensors_count//2, dtype=numpy.float32)/(sensors_count*0.5))
        weights_right = +(1.0/(sensors_count//2) + range(sensors_count//2)*numpy.ones(sensors_count//2, dtype=numpy.float32)/(sensors_count*0.5))

        weights       = numpy.hstack((weights_left, weights_right))

        distances     = numpy.expand_dims(points, 1) - numpy.expand_dims(weights, 0)
        distances     = distances + 0.01*numpy.random.randn(distances.shape[0], distances.shape[1])
        distances     = distances**2        
        result        = numpy.exp(-filter_k*distances)

        result[result < 0.01] = 0.0

        return result

    def _points_to_labels(self, points, threshold = 0.3):
        count  = points.shape[0]
        result = numpy.zeros((3, count), dtype=numpy.float32)

        left_position   = points < -threshold
        right_position  = points >  threshold
        center_position = numpy.logical_not(numpy.logical_or(left_position, right_position))

        result[0] = left_position
        result[1] = center_position
        result[2] = right_position

        result    = numpy.transpose(result)

        return result

 
class DatasetLineFollowerStream:
    def __init__(self, sequence_length = 128, prediction_step = 8, training_count = 10000, testing_count = 1000):
        
        nominal_velocity    = 1.0       #1m/s
        minimum_radius      = 0.05      #5cm
        sensors_brace       = 0.08      #8cm
        sampling_frequency  = 200       #200Hz 
        sensors_count       = 8         #8

        self.sequence_length = sequence_length 
        self.prediction_step = prediction_step

        self.training_count  = training_count
        self.testing_count   = testing_count

        self.input_shape   = (self.sequence_length, sensors_count)
        self.output_shape  = (self.sequence_length, 3)


        self.training_x = numpy.zeros((self.training_count, ) + self.input_shape,   dtype=numpy.float32)
        self.training_y = numpy.zeros((self.training_count, ) + self.output_shape,  dtype=numpy.float32)
        self.testing_x  = numpy.zeros((self.testing_count, ) + self.input_shape,    dtype=numpy.float32)
        self.testing_y  = numpy.zeros((self.testing_count, ) + self.output_shape,   dtype=numpy.float32)


        self.points_training = LinePoints(training_count + prediction_step + sequence_length, nominal_velocity, minimum_radius, sensors_brace, sampling_frequency, sensors_count)
        self.points_testing  = LinePoints(testing_count  + prediction_step + sequence_length, nominal_velocity, minimum_radius, sensors_brace, sampling_frequency, sensors_count)
        

        for i in range(self.training_count):
            training_x, training_y = self._create_item(self.points_training.sensors, self.points_training.points[0], self.points_training.labels, i)
            self.training_x[i] = training_x.copy()
            self.training_y[i] = training_y.copy()


        for i in range(self.testing_count):
            testing_x, testing_y = self._create_item(self.points_testing.sensors, self.points_testing.points[0], self.points_testing.labels, i)
            self.testing_x[i] = testing_x.copy()
            self.testing_y[i] = testing_y.copy()


    def get_training_count(self):
        return len(self.training_x)

    def get_testing_count(self):
        return len(self.testing_x)

    def get_training_batch(self, batch_size = 32):
        return self._get_batch(self.training_x, self.training_y, batch_size)

    def get_testing_batch(self, batch_size = 32):
        return self._get_batch(self.testing_x, self.testing_y, batch_size)


    def _get_batch(self, x, y, batch_size):
        result_x = torch.zeros((batch_size, ) + self.input_shape)
        result_y = torch.zeros((batch_size, ) + self.output_shape)

        for i in range(batch_size): 
            idx = numpy.random.randint(len(x))

            result_x[i]  = torch.from_numpy(x[idx]).float()
            result_y[i]  = torch.from_numpy(y[idx]).float()

        return result_x, result_y

    def _create_item(self, sensors, points, labels, idx):
        result_x = sensors[idx : idx+self.sequence_length]
        #result_y = points[idx + self.prediction_step : idx + self.sequence_length + self.prediction_step]
        #result_y = numpy.expand_dims(result_y, 1)

        result_y = labels[idx + self.prediction_step : idx + self.sequence_length + self.prediction_step]
        return result_x, result_y 



if __name__ == "__main__":
    dataset = DatasetLineFollowerStream()

    #lp = LinePoints(points_count=1000)
    
