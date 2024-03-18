import machine
import time
import re

i2c = machine.I2C(1,sda=machine.Pin(18),scl=machine.Pin(19),timeout=500_000)
devs = i2c.scan()
print(devs)
while True:
    #i2c.writeto(55,bytearray(0x01))
    b = i2c.readfrom(49,19)
    #print(b)
    d = re.sub("[^a-z0-9]+","", b.decode('utf-8'))
    #print(d)
    try:
        i = int(d)
        #print(f'success: {i}')
        if d[0] != '0':
            print(f'success: {i}')
    except Exception as e:
        print(e)
        print(b)
        print(d)
    
    time.sleep(0.1)

