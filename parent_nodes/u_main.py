import machine
import time
import sys
import re
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
    41: 'Arduino Uno R4 Wifi', # untested
    42: 'Arduino Nano', # untested
    43: 'Pico', # tested, working
    45: 'ESP32', # tested, working
    46: 'ESP32C3', # tested, working
    47: 'NRF52840 Sense', # tested, working
    48: 'STM32F401CCUX', # tested, working
    49: 'Pro Micro', # tested, working
    50: 'ESP8266', # not working
    51: 'Teensy 4.0', # tested, working
    52: 'ItsyBitsy M0', # tested, working
    53: 'ItsyBitsy M4',
    54: 'Renasas RA4M1', # tested, working
    55: 'STM32G474CETX', # tested, working
    56: 'STM32F103RCT6', # tested, working
    57: 'STM32F103C8T6' # tested, working
    }

def update_loop(i2c,uart):
    global lcd_connected
    #devs = i2c.scan() # this line crashes on nrf
    #print(devs)
    for dev in devices:
        #if dev not in list(devices.keys()):
            #continue
        try:
            b = i2c.readfrom(dev,19)
            #print(b)
            d = re.sub("[^a-z0-9]+","", b.decode('utf-8'))
            if int(d)==0:
                continue
            while d[-1] == "0":
                d = d[:-1]
            print(f'Received: {d} from {devices[dev]}')
        except Exception as e:
            print(e)
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
    i2c = machine.I2C(1,sda=machine.Pin(18), scl=machine.Pin(19),timeout=500_000)
    if lcd_connected:
        lcd.setRGB(50,50,50);
else:
    i2c = machine.I2C(-1,sda=machine.Pin(21),scl=machine.Pin(22))

uart = machine.UART(0,9600)

while True:
    update_loop(i2c,uart)
    time.sleep(0.2)
    