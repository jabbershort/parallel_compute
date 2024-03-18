#include <Wire.h>
#include "limits.h"
#include "math_functions.h"
#include "board_properties.h"

struct result {
  bool collected;
  uint64_t result;
  char resultString[19];
  int timeTaken;
  char* board;
};

char zero_result[] = "0000000000000000000";
result latest_prime;

void print_prime() {
  Serial.print(latest_prime.board);
#if !defined(ARDUINO_SEEED_XIAO_NRF52840_SENSE)
  Serial.print(" (");
  Serial.print(F_CPU / 1000000);
  Serial.print("MHz): ");
#else
  Serial.print(":");
#endif
  Serial.print(latest_prime.resultString);
  Serial.print(". Time taken: ");
  Serial.print(latest_prime.timeTaken);
  Serial.println("ms.");
}

void generate_prime() {
  int start = millis();
  int k = 40;
  uint64_t r;
  bool pr = false;
  while (pr == false) {
    r = getRandom(0, UINT64_MAX);
    pr = isPrime(r, k);
    #if defined(ARDUINO_ESP8266_WEMOS_D1MINI)
      yield();
    #endif
  }
  latest_prime.timeTaken = millis() - start;
  latest_prime.result = r;
  uintToStr(r,latest_prime.resultString);
  latest_prime.collected = false;
  digitalWrite(LED_PIN, !digitalRead(LED_PIN));
}

void onReceive(int howMany) {
  // Serial.print("Received: ");
  // Serial.println(howMany);
}

#if defined(ARDUINO_ARC32_TOOLS)
void handleUART() {
  if (Serial1.available() > 0) {
    if (latest_prime.collected == false) {
      Serial1.print(latest_prime.resultString);
      latest_prime.collected = true;
    } else {
      Serial1.print(zero_result);
    }
  }
}
#endif

void onRequest() {
  if (latest_prime.collected)
  {
    #if defined(ARDUINO_MINIMA) || defined (ARDUINO_ITSYBITSY_M0)
      Wire.write(zero_result);
    #elif defined(ARDUINO_SEEED_XIAO_NRF52840_SENSE) || defined(ARDUINO_Seeed_XIAO_nRF52840_Sense) || defined (ARDUINO_AVR_PROMICRO)
      for(int i = 0;i<19;i++)
      {
        Wire.write(zero_result[i]);
      }
    #else
      for(int i = 0;i<19;i++)
      {
        Wire.write(zero_result[i]);
      }
      Wire.endTransmission();
    #endif
  }
  else {
    #if defined(ARDUINO_MINIMA) || defined (ARDUINO_ITSYBITSY_M0)
      Wire.write(latest_prime.resultString);
      latest_prime.collected = true;
    #elif defined(ARDUINO_SEEED_XIAO_NRF52840_SENSE) || defined(ARDUINO_Seeed_XIAO_nRF52840_Sense) || defined (ARDUINO_AVR_PROMICRO)
      for(int i = 0;i<19;i++)
      {
        Wire.write(latest_prime.resultString[i]);
      }
      latest_prime.collected = true;
    #else
      for(int i = 0;i<19;i++)
      {
        Wire.write(latest_prime.resultString[i]);
      }
      Wire.endTransmission();
      latest_prime.collected = true;
    #endif
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

#if defined(ARDUINO_RASPBERRY_PI_PICO) || defined(ARDUINO_RASPBERRY_PI_PICO_W) || defined(ARDUINO_GENERIC_F401CCUX) || defined(ARDUINO_GENERIC_G474CETX) || defined(ARDUINO_GENERIC_F103RCTX) || defined(ARDUINO_GENERIC_F103C8TX) || defined(ARDUINO_TEENSY40)
  Wire.setSDA(SDA_PIN);
  Wire.setSCL(SCL_PIN);
#endif

#if defined(ARDUINO_ARC32_TOOLS)
  Serial1.begin(9600);
#elif defined(ARDUINO_Seeed_XIAO_nRF52840_Sense) || defined(ARDUINO_SEEED_XIAO_NRF52840_SENSE)
  Wire.setClock(400000);
  Wire.begin(ADDRESS);
  Wire.onReceive(onReceive);
  Wire.onRequest(onRequest);
#elif defined(ARDUINO_ESP32_DEV)
  Wire.begin((uint8_t)ADDRESS, SDA_PIN, SCL_PIN, 400000);
  Wire.onReceive(onReceive);
  Wire.onRequest(onRequest);
#elif defined(ARDUINO_ESP8266_WEMOS_D1MINI)
  Wire.begin(SDA_PIN,SCL_PIN,ADDRESS);
  Wire.onReceive(onReceive);
  Wire.onRequest(onRequest);
#elif defined(ARDUINO_GENERIC_G474CETX) || defined(ARDUINO_GENERIC_F103C8TX) // || defined(ARDUINO_GENERIC_F103RCTX) this seems not to be required
  Wire.setClock(400000);
  Wire.begin(ADDRESS,true,false);
  Wire.onReceive(onReceive);
  Wire.onRequest(onRequest);
#else
  Wire.begin(ADDRESS);
  Wire.onReceive(onReceive);
  Wire.onRequest(onRequest);
#endif

#if defined(ARDUINO_AVR_PROMICRO)
  Wire.setWireTimeout(100000,true);
#endif

latest_prime.result = 0;
latest_prime.timeTaken = 0;
latest_prime.board = (char*)boardname;
delay(5000);
Serial.print("Starting device: ");
Serial.print(boardname);

#if defined(ARDUINO_ARC32_TOOLS)
  Serial.print(". On UART");
#else
  Serial.print(". On I2C address: ");
  Serial.print(ADDRESS);
#endif
#if defined(ARDUINO_RASPBERRY_PI_PICO) || defined(ARDUINO_RASPBERRY_PI_PICO_W) || defined(ARDUINO_GENERIC_F401CCUX) || defined(ARDUINO_ESP32_DEV) || defined(ARDUINO_GENERIC_G474CETX) || defined(ARDUINO_GENERIC_F103RCTX) || defined(ARDUINO_GENERIC_F103C8TX)
  Serial.print(". Using SDA ");
  Serial.print(SDA_PIN);
  Serial.print(" and SCL ");
  Serial.print(SCL_PIN);
#endif
  Serial.println(".");
}

void loop() {
#if defined(ARDUINO_ARC32_TOOLS)
  handleUART();
#endif
  generate_prime();
  print_prime();
  // delay(2000);
}
