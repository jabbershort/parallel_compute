import machine
import time

i2c = machine.I2C(1,sda=machine.Pin(18),scl=machine.Pin(19))
devs = i2c.scan()
print(devs)
while True:
    b = i2c.readfrom(85,1,False)
    print(b)
    time.sleep(1)

