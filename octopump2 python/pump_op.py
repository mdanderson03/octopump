import time
from octopump2 import octopump

arduino = octopump.initialize('COM4')
# command form is octopump.motor(arduino, pump number (int), pwm duty cycle (int)). Range for PWM is 0-99.
# PWM of 0 turns motor off.
# PWM values < 5 are unstable and unreliable. Use at own risk.
# Flow rate range. PWM of 5 has rate 10 uL/sec and PWM of 99 has rate of 1600 uL/sec
#5 sec lag exist when starting program to establish stable serial connection with arduino

octopump.motor(arduino, 1, 25)
time.sleep(6)
octopump.motor(arduino, 1, 0)
