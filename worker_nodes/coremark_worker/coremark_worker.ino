// CoreMark Benchmark for Arduino compatible boards
//   original CoreMark code: https://github.com/eembc/coremark

#include "coremark_worker.h"
#include "board_properties.h"

void setup()
{
  // pinMode(LED_PIN, OUTPUT);
  // digitalWrite(LED_PIN, HIGH); 
	Serial.begin(9600); 
	while (!Serial) ; // wait for Arduino Serial Monitor
	delay(500);
  Serial.print("{\"board\":\"");
  Serial.print(boardname);
  Serial.print("\",\"processor\": \"");
  Serial.print(processorname);
  Serial.print("\",\"core\":\"");
  Serial.print(corename);
  #if !defined(ARDUINO_SEEED_XIAO_NRF52840_SENSE)
  Serial.print("\",\"frequency (MHz)\":");
  Serial.print(F_CPU/1000000);
  #else
  Serial.print("\"");
  #endif
	int res = coremark_main(); // Run the benchmark  :-)
  Serial.print(",\"score\":");
  Serial.print(res);
  Serial.println("}");
  // digitalWrite(LED_PIN, LOW); 
}

void loop()
{
}
