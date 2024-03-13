#include <Wire.h>
 
byte TxByte = 0xAA;
const int LED = LED_BUILTIN;
 
void I2C_TxHandler(void)
{
  digitalWrite(LED,!digitalRead(LED));

  Wire.write(TxByte);
  Serial.println("receiced");
}
 
void setup() {
  Serial.begin(9600);
  pinMode(LED,OUTPUT);
  // Wire.setSDA(PB7);
  // Wire.setSCL(PB6);
  Wire.begin(0x55); // Initialize I2C (Slave Mode: address=0x55 )
  Wire.onRequest(I2C_TxHandler);
}
 
void loop() {
  // Nothing To Be Done Here
}