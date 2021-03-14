import numpy

class DCMotor:

    """
    :param nominal_voltage: [V]
    :param no_load_speed: [rad/s]
    :param stall_torque: [Nm]
    """
    def __init__(self, nominal_voltage, no_load_speed, stall_torque):
        self.motor_constant = nominal_voltage / no_load_speed
        self.resistance     = nominal_voltage / stall_torque * self.motor_constant


    '''
    compute output motor torque in [Nm]
    :param supply_voltage [V]
    :param w: [rad/s]
    :return: shaft torque [Nm]
    '''
    def get_torque(self, supply_voltage, w):
        return (supply_voltage - w*self.motor_constant) / self.resistance*self.motor_constant


if __name__ == "__main__":
    nominal_voltage   = 6                        #6Volts
    no_load_speed     = 1000*2.0*numpy.pi/60.0   #1000rpm
    stall_torque      = 0.57*0.09807             #0.57kg.cm

    wheel_radius      = 32.0/2000.0              #wheel diameter is 32mm
    wheel_mass        = 5.0/1000.0               #wheel weight 5grams
    wheel_inertia     = 0.5*wheel_mass*(wheel_radius**2)


    motor = DCMotor(nominal_voltage, no_load_speed, stall_torque)

    dt = 0.000001
    v  = 0.0
    v_rad = 0.0
    for n in range(100):
        pwm = 255.0
        

        torque = motor.get_torque(nominal_voltage*pwm/255.0, v_rad)
        
        v = v + (torque/wheel_inertia)*dt
        v_rad = v*(numpy.pi/wheel_radius)

        print(n, torque, v, v_rad*60.0/(2.0*numpy.pi))
