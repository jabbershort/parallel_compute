# -*- coding: utf-8 -*-
import time
import math
from RGB1602 import RGB1602

colorR = 64
colorG = 128
colorB = 64

lcd=RGB1602(16,2)

t=0

while True:
    
    
  
    r = int((abs(math.sin(3.14*t/180)))*255);
    g = int((abs(math.sin(3.14*(t+60)/180)))*255);
    b = int((abs(math.sin(3.14*(t+120)/180)))*255);
    t = t + 3;
  
  
    lcd.setRGB(r,g,b);
# set the cursor to column 0, line 1
    for i in range(0,16):
        lcd.setCursor(i, 0)
        lcd.printout('1')
        time.sleep(0.3)
# print the number of seconds since reset:

# print the number of seconds since reset:
    lcd.printout("Waveshare")
  
    lcd.setCursor(0, 1)
  
    lcd.printout("Hello,World!")
    time.sleep(0.3)

