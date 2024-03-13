import machine
import time

i2c = machine.I2C(1,sda=machine.Pin(18),scl=machine.Pin(19))
while True:
    print(i2c.scan())
    time.sleep(1)