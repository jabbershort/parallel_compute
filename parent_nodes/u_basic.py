import machine
import time

i2c = machine.I2C(1,sda=machine.Pin(18),scl=machine.Pin(19),timeout=500_000)
devs = i2c.scan()
print(devs)
while True:
    b = i2c.readfrom(51,19)
    print(b)
    d = b.decode('utf-8')
    print(d)
    i = int(d)
    print(i)
    time.sleep(1)

