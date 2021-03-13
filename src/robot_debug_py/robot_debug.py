import numpy

class RobotDebug:

    def __init__(self):
        pass


    def update(self, gui, json_data):

        json_data = json_data["debug"]
        
        sensors_count = len(json_data["line_sensor"]["adc_result"])
        line_sensors = numpy.zeros(sensors_count)
        for i in range(sensors_count):
            line_sensors[i] = float(json_data["line_sensor"]["adc_result"][i])
        
        gui.variables.add("line_sensors", line_sensors)

        angles = {}
        angles[0] =  float(json_data["imu_sensor"]["angle"][0])*(+0.1)
        angles[1] =  float(json_data["imu_sensor"]["angle"][1])*(-0.1)
        angles[2] =  float(json_data["imu_sensor"]["angle"][2])*(+0.1)

        gui.variables.add("imu_angles", angles)


        distance_sensors = numpy.zeros(3)
      
        distance_sensors[0] =  float(json_data["distance_sensor"]["right"])
        distance_sensors[1] =  float(json_data["distance_sensor"]["front"])
        distance_sensors[2] =  float(json_data["distance_sensor"]["left"])

        gui.variables.add("distance_sensors", distance_sensors)



        line_position = ""

        line_position+= "line_lost_type   = " + str(json_data["line_sensor"]["line_lost_type"]) + "\n"
        line_position+= "line_lost   = " + str(json_data["line_sensor"]["line_type"]) + "\n"
        line_position+= "on_line_count = " + str(json_data["line_sensor"]["on_line_count"]) + "\n"
        line_position+= "center = " + str(round(float(json_data["line_sensor"]["center_line_position"]), 2)) + "\n"
        line_position+= "left = " + str(round(float(json_data["line_sensor"]["left_line_position"]), 2)) + "\n"
        line_position+= "right = " + str(round(float(json_data["line_sensor"]["right_line_position"]), 2)) + "\n"
        line_position+= "average = " + str(json_data["line_sensor"]["average"]) + "\n"


        gui.variables.add("line_position", line_position)


        motors = ""

        motors+= "left distance  = "    + str(round(float(json_data["motor_controll"]["left_encoder"]), 0)) + "[mm]\n"
        motors+= "left speed     = "    + str(round(float(json_data["motor_controll"]["left_speed"]), 4)) + "\n"
        motors+= "right distance = "    + str(round(float(json_data["motor_controll"]["right_encoder"]), 0)) + "[mm]\n"
        motors+= "right speed     = "   + str(round(float(json_data["motor_controll"]["right_speed"]), 4)) + "\n"

        gui.variables.add("motors_output", motors)


        camera = []

        camera_size = 8
        idx = 0
        for j in range(camera_size):
            line = []
            for i in range(camera_size):
                line.append(float(json_data["neural_network"]["input"][idx]))
                idx+= 1

            camera.append(line)

        gui.variables.add("camera", camera)

        network_outputs_count = len(json_data["neural_network"]["network_output"])
        network_output = numpy.zeros(network_outputs_count)
        for i in range(network_outputs_count):
            network_output[i] = float(json_data["neural_network"]["network_output"][i])

        gui.variables.add("classification_result", network_output)

       
        
