from opengl_gui.widget_frame import WidgetFrame
import numpy

class WidgetGraph(WidgetFrame):
    def __init__(self, visualisation, variables, textures, params):
        super().__init__(visualisation, variables, textures, params)

        self.br  = float(params["bar_color"][0])
        self.bg  = float(params["bar_color"][1])
        self.bb  = float(params["bar_color"][2])

        
        #self.k = (max_out-min_out)/(self.max-self.min)
        #self.q = max_out - self.k*self.max

    def render(self):
        if self.visible:
            self.visualisation.push()   
            self.visualisation.translate(self.x, self.y, self.z)

            self.render_frame()

            highlight_idx   = self.variables.v[self.variable_name][0]
            values_x        = numpy.asarray(self.variables.v[self.variable_name][1])
            values_y        = numpy.asarray(self.variables.v[self.variable_name][2])
            
            count   = values_x.shape[0]
            
            min_x   = numpy.min(values_x)
            max_x   = numpy.max(values_x)

            min_y   = numpy.min(values_y)
            max_y   = numpy.max(values_y)

            
            max_x_out = self.width*0.99*0.5
            min_x_out = -self.width*0.99*0.5

            max_y_out = self.height*0.99*0.5
            min_y_out = -self.height*0.99*0.5
            

            kx = (max_x_out - min_x_out)/(max_x - min_x)
            qx = max_x_out  - kx*max_x

            ky = (max_y_out - min_y_out)/(max_y - min_y)
            qy = max_y_out  - ky*max_y


            for i in range(count-1):
                x_raw0 = values_x[i]
                y_raw0 = values_y[i]

                x_raw1 = values_x[i+1]
                y_raw1 = values_y[i+1]


                x0 = kx*x_raw0 + qx
                y0 = ky*y_raw0 + qy

                x1 = kx*x_raw1 + qx
                y1 = ky*y_raw1 + qy

                
                self.visualisation.set_color(self.br, self.bg, self.bb)
                self.visualisation.paint_line(x0, y0, 0.01, x1,  y1,  0.01)

                self.visualisation.push()   
                

                if i == highlight_idx:
                    self.visualisation.translate(x0, y0, 0.011)
                    self.visualisation.set_color(1.0, 0.0, 0.0)
                    self.visualisation.paint_circle(1.5*self.frame_width)
                else:
                    self.visualisation.translate(x0, y0, 0.01)
                    self.visualisation.set_color(self.br, 2.0*self.bg, self.bb)
                    self.visualisation.paint_circle(0.5*self.frame_width)
                
                self.visualisation.pop()
                
                '''
                w  = self.width*0.9
                rw = w/count
                rh = value

                x_ = -self.width/2.0 + rw*0.9 + i*rw*1.05
                y_ = -rh/2.0 + self.height/2.0

                self.visualisation.push()

                self.visualisation.set_color(self.br, self.bg, self.bb)

                self.visualisation.translate(x_, -y_, 0.01)
                self.visualisation.paint_rectangle(rw, rh)
                self.visualisation.pop()

            
                self.visualisation.push()
                string = self._get_rounded(v_raw, 2)

                
                self.visualisation.print_string(x_ - rw/4.0, -y_ + rh/2.0 + 0.01, 0, string, self.font_size*0.5)
                self.visualisation.pop()
                '''

            for i in range(len(self.child_widgets)):
                self.child_widgets[i].render()

            self.visualisation.pop()


    def _get_rounded(self, value, precision):
        return str(round(value, precision))
