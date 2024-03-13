import machine
import time
import sys
#from RGB1602 import RGB1602

lcd_connected = False

#primes = []
if sys.implementation._machine == 'Raspberry Pi Pico with RP2040':
    try:
        lcd=RGB1602(16,2)
        lcd_connected = True
    except:
        print('Failed to connect to screen')
        lcd_connected=False

devices = {
    42: 'Arduino Nano',
    43: 'Pico',
    45: 'ESP32',
    46: 'ESP32C3',
    47: 'NRF52840 Sense',
    48: 'STM32F401CCUX',
    49: 'Pro Micro'
    }

def update_loop(i2c,uart):
    global lcd_connected
    devs = i2c.scan()
    #print(devs)
    for dev in devs:
        if dev not in list(devices.keys()):
            continue
        try:
            b = i2c.readfrom(dev,19)
            print(b)
            d = int(b.decode('utf-8'))
            if d < 5:
                continue
            print(f'Received: {d} from {devices[dev]}')
        except:
            continue

        #if sys.implementation._machine == 'Raspberry Pi Pico with RP2040':
            #if lcd_connected:
                #print_prime(d)
    #read uart
    # uart.write('hi')
    # d = uart.readline()
    # print(d)

def print_prime(num):
    global lcd
    lcd.setCursor(0,0)
    num = str(num)
    lcd.printout(num[0:15])
    lcd.setCursor(0,1)
    lcd.printout(num[15:])

if sys.implementation._machine == 'Raspberry Pi Pico with RP2040':
    i2c = machine.I2C(1,sda=machine.Pin(18), scl=machine.Pin(19))
    if lcd_connected:
        lcd.setRGB(50,50,50);
else:
    i2c = machine.I2C(-1,sda=machine.Pin(21),scl=machine.Pin(22))

uart = machine.UART(0,9600)

while True:
    update_loop(i2c,uart)
    time.sleep(0.1)
    