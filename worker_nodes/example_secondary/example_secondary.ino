#include <Wire.h>
 
byte zero_result[] = {0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19};
const int LED = LED_BUILTIN;
 
void I2C_TxHandler(void)
{
  digitalWrite(LED,!digitalRead(LED));
  for (int i = 0;i<19;i++)
  {
        Wire.write(zero_result[i]);
  }
  // Wire.endTransmission();
}
 
void setup() {
  Serial.begin(9600);
  pinMode(LED,OUTPUT);  
  Wire.begin(55);
  Wire.onRequest(I2C_TxHandler);
}
 
void loop() {
  // Nothing To Be Done Here

}