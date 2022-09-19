import serial
import time

class octopump:

    def initialize(serial_com):
        arduino = serial.Serial(port=serial_com, baudrate=9600, timeout=5)
        time.sleep(5)
        return arduino

    def motor(serial_obj, motor, dig_speed):
        finished = 1
        if dig_speed < 10:
            command = str(motor) + str(0) + str(dig_speed)
        elif dig_speed >= 10 and dig_speed <= 99:
            command = str(motor) + str(dig_speed)
        elif dig_speed >= 100:
            print('Too high of dig_speed value. Please rerun and use integer between 0 and 99')
            raise SystemExit(0)
        command = command.encode()
        serial_obj.write(command)
        while finished != 0:
            finished = serial_obj.readline()
            finished = finished.decode()
            try:
                finished = int(finished)
            except:
                finished = 1
        if dig_speed >= 5:
            flow_rate = -.0012*dig_speed*dig_speed*dig_speed + 0.226*dig_speed*dig_speed + 6.1519*dig_speed - 18.33
            print('pump ' + str(motor) + ' at PWM of ' + str(dig_speed) + ' has approx free flow rate of uL/s: ' + str(flow_rate))
        else:
            print('approx flow rate in uL/s: 0' )
        return
