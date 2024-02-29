import machine
import time

i2c = machine.I2C(0,sda=machine.Pin(20),scl=machine.Pin(21))
while True:
    print(i2c.scan())
    time.sleep(1)