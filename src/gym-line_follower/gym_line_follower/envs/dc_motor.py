import numpy
import matplotlib.pyplot as plt

class DCMotor:
    '''
    nominal_voltage [V]
    no_load_rpm     [rpm]
    stall_torque    [kg.cm]
    '''
    def __init__(self, nominal_voltage, no_load_rpm, stall_torque):

        no_load_speed       = no_load_rpm*(2.0*numpy.pi/60.0)
        stall_torque        = 0.09807*stall_torque  

        self.motor_constant = nominal_voltage / no_load_speed
        self.resistance     = nominal_voltage / stall_torque * self.motor_constant

    '''
    supply_voltage [V]
    rpm     [rpm]
    returns torque in Nm
    '''
    def step(self, supply_voltage, rpm):
        speed   = rpm*(2.0*numpy.pi/60.0)
        return (supply_voltage - speed*self.motor_constant) / self.resistance*self.motor_constant


if __name__ == "__main__":
    nominal_voltage   = 6       #6Volts
    no_load_speed     = 1000    #1000rpm
    stall_torque      = 0.57    #0.57kg.cm

    wheel_radius      = 32.0*0.5/1000.0    #wheel diameter is 32mm
    wheel_mass        = 0.01               #wheel weight 10 grams
    wheel_inertia     = 0.5*wheel_mass*(wheel_radius**2)


    motor = DCMotor(nominal_voltage, no_load_speed, stall_torque)

    dt      = 0.001
    t_max   = 1.0

    t       = 0.0
    speed   = 0

    l_time    = []
    l_voltage = []
    l_torque  = []
    l_speed   = []

    while t < t_max:
        v = 0.0
        if t > 0.1*t_max:
            v = 0.5*nominal_voltage
        if t > 0.2*t_max:
            v = nominal_voltage
        if t > 0.5*t_max:
            v = 0.0
        if t > 0.75*t_max:
            v = nominal_voltage

        torque = motor.step(v, speed)

        speed  = speed + (torque/wheel_inertia)*dt

        l_voltage.append(v)
        l_time.append(t)
        l_torque.append(torque/0.09807)
        l_speed.append(speed)

        t+= dt
        
        print(t, torque, speed)

    plt.subplot(311)
    plt.ylabel('voltage [V]')
    plt.xlabel('time [s]')
    plt.plot(l_time, l_voltage, color='salmon')

    plt.subplot(312)
    plt.ylabel('speed [RPM]')
    plt.xlabel('time [s]')
    plt.plot(l_time, l_speed, color='deepskyblue')

    plt.subplot(313)
    plt.ylabel('torque [kg.cm]')
    plt.xlabel('time [s]')
    plt.plot(l_time, l_torque, color = 'yellowgreen')
    
    plt.show()
