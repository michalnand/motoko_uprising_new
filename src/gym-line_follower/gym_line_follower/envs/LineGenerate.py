import numpy
import matplotlib.pyplot as plt
import json


class LineModel:
    def __init__(self, line_base_points, width, file_name_prefix):
        self.line_base_points   = line_base_points
        self.width              = width

        self.decimal_places = 5
        self._create_line_points()

        self.urdf_str = "<?xml version=\"0.0\" ?>\n\
<robot name=\"plane\">\n\
<link name=\"planeLink\">\n\
<contact>\n\
    <lateral_friction value=\"1\"/>\n\
</contact>\n\
    <inertial>\n\
    <origin rpy=\"0 0 0\" xyz=\"0 0 0\"/>\n\
    <mass value=\".0\"/>\n\
    <inertia ixx=\"0\" ixy=\"0\" ixz=\"0\" iyy=\"0\" iyz=\"0\" izz=\"0\"/>\n\
    </inertial>\n\
    <visual>\n\
    <origin rpy=\"0 0 0\" xyz=\"0 0 0.004\"/>\n\
        <geometry>\n\
            <mesh filename=\"{}\" scale=\"1 1 1\" />\n\
        </geometry>\n\
        <material name=\"line_color\">\n\
            <color rgba=\"0 0 0 1\" />\n\
        </material>\n\
    </visual>\n\
    <collision>\n\
    <origin rpy=\"0 0 0\" xyz=\"0 0 -5\"/>\n\
    <geometry>\n\
        <box size=\"10 10 10\"/>\n\
    </geometry>\n\
    </collision>\n\
</link>\n\
</robot>"

        self._save(file_name_prefix)

    def _get_length(self):
        return self.points.shape[0]

    def _save(self, file_name_prefix):

        f_obj  = open(file_name_prefix + ".obj", "w") 
        f_json = open(file_name_prefix + ".json", "w") 
        f_urdf = open(file_name_prefix + ".urdf", "w") 

        idx_current = 1

        
        for i in range(self._get_length()-3):
            
            points_now   = self._get_points(self.width, self.points[i + 0], self.points[i + 1])
            points_next  = self._get_points(self.width, self.points[i + 1], self.points[i + 2])

            points = []
            points.append(points_now[0])
            points.append(points_next[1])
            
            points_str, idx_current = self._get_obj(points, idx_current)

            f_obj.write(points_str)
        
        f_obj.flush()
        f_obj.close()

        points = numpy.round(self.points, self.decimal_places).tolist()
        
        json_data           = {}
        json_data["count"]  = self._get_length()
        json_data["points"] = points
                  
        json_str = json.dumps(json_data)
        f_json.write(json_str)

        f_json.flush()
        f_json.close()

        f_urdf.write(self.urdf_str.format(file_name_prefix + ".obj"))
        f_urdf.flush()
        f_urdf.close()

    def _create_line_points(self):
        self.base_points = numpy.zeros((self.line_base_points, 2), dtype=numpy.float32)

        radius_max      = 4.0
        radius_min      = 0.05
        p_curve_change  = 0.5
    
        dphi            = 2.0*numpy.pi/self.line_base_points
        if numpy.random.randint(2) == 0:
            dphi = -dphi

        phi = 0.0
 
        radius = self._random_radius(radius_min, radius_max)
        radius_new = radius
       
        k = 0.5
        for i in range(self.line_base_points):

            if numpy.random.rand() < p_curve_change:
                radius_new = self._random_radius(radius_min, radius_max)

            radius = (1.0 - k)*radius + k*radius_new
             
            x = radius*numpy.sin(phi)
            y = radius*numpy.cos(phi)
            phi+= dphi

            self.base_points[i][0] = x
            self.base_points[i][1] = y

        self._interpolate(32)

    def _interpolate(self, interpolation_steps):
        self.line_base_points = self.base_points.shape[0]
        self.points = numpy.zeros((self.line_base_points*interpolation_steps, 2), dtype=numpy.float32)

        idx = 0
        for j in range(self.line_base_points):
            for i in range(interpolation_steps):
                k = i/(interpolation_steps-1)
                
                p0 = self.base_points[(j+0)%self.line_base_points]
                p1 = self.base_points[(j+1)%self.line_base_points]
                p2 = self.base_points[(j+2)%self.line_base_points]
                p3 = self.base_points[(j+3)%self.line_base_points]

                self.points[idx] = self._interpolate_point(p0, p1, p2, p3, k)
                idx+= 1

    def _interpolate_point(self, p0, p1, p2, p3, mu):
        
        mu2 = mu**2
        a0 = p3 - p2 - p0 + p1
        a1 = p0 - p1 - a0
        a2 = p2 - p0
        a3 = p1

        p = a0*mu*mu2 + a1*mu2 + a2*mu + a3
        return p

    def _random_radius(self, min, max):
        r = numpy.random.rand()
        return (1.0 - r)*min + r*max

    def show(self, file_name = None):
        
        tmp      = numpy.transpose(self.points)
        tmp_base = numpy.transpose(self.base_points)
        plt.clf()
        plt.plot(tmp[0], tmp[1])
        plt.plot(tmp_base[0], tmp_base[1])

        if file_name is not None:
            plt.savefig(file_name)
        else:
            plt.show()


    def _get_points(self, width, start_point, end_point):

        x0 = start_point[0]
        y0 = start_point[1]

        x1 = end_point[0]
        y1 = end_point[1]
        
        #vector
        vx = x1 - x0
        vy = y1 - y0

        #perpindicular vector
        vxp = vy
        vyp = -vx

        #normalise vector
        length = (vxp**2 + vyp**2)**0.5

        vxp = vxp / length
        vyp = vyp / length

        points = []

        points.append([x0 + vxp*0.5*width, y0 + vyp*0.5*width])
        points.append([x0 - vxp*0.5*width, y0 - vyp*0.5*width])
        points.append([x1 + vxp*0.5*width, y1 + vyp*0.5*width])
        points.append([x1 - vxp*0.5*width, y1 - vyp*0.5*width])

        return points


    def _get_obj(self, points, idx_start = 1):
        idx_end = len(points) + idx_start
        
        result = ""

        for i in range(len(points)):
            result+= "v " + str(round(points[i][0], self.decimal_places)) + " " + str(round(points[i][1], self.decimal_places)) + " " + str(0.0) + "\n"

        result+= "f " + str(idx_start + 0) + " " + str(idx_start + 2) + " " + str(idx_start + 1) + "\n"
        result+= "f " + str(idx_start + 2) + " " + str(idx_start + 3) + " " + str(idx_start + 1) + "\n"

        return result, idx_end


if __name__ == "__main__":

    for i in range(64):
        line_base_points   = 16
        line_width         = 0.015     #15mm
        line = LineModel(line_base_points, line_width, "./models/lines/" + str(i))

