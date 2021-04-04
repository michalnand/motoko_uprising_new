from opengl_gui.widget_frame import WidgetFrame

import numpy

class WidgetImageFrame(WidgetFrame):
    def __init__(self, visualisation, variables, textures, params):
        super().__init__(visualisation, variables, textures, params)
        
        
    def render(self):
        if self.visible:
            value = self.variables.v[self.variable_name]

            texture_id = self.textures.get(value)

            self.visualisation.push()
            self.visualisation.translate(self.x, self.y, self.z)
            self.render_frame()


            self.visualisation.push()
            self.visualisation.set_color(1, 1, 1)

            k = 0.99
            #self.visualisation.translate(0.0, 0.0, 0.0)
            self.visualisation.paint_textured_rectangle(self.width*k, self.height*k, texture_id)

            self.visualisation.pop()

            for i in range(len(self.child_widgets)):
                self.child_widgets[i].render()

            self.visualisation.pop()
