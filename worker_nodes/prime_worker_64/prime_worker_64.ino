#include <Wire.h>
#include "limits.h"
#include "math_functions.h"
#include "board_properties.h"

union prime{
  uint64_t num;
  byte uBytes[8];
};

struct result{
  bool collected;
  prime result;
  int timeTaken;
  char* board;
};

uint64_t zero_result = 0;
result latest_prime;

void print_prime()
{
  char num_str[21];
  Serial.print(latest_prime.board);
  #if !defined(ARDUINO_SEEED_XIAO_NRF52840_SENSE) 
  Serial.print(" (");
  Serial.print(F_CPU/1000000);
  Serial.print("MHz): ");
  #else
  Serial.print(":" );
  #endif
  Serial.print(uintToStr(latest_prime.result.num,num_str));
  Serial.print(". Time taken: ");
  Serial.print(latest_prime.timeTaken);
  Serial.println("ms.");
}

void generate_prime()
{
  int start = millis();
  int k = 20;
  uint64_t r;
  bool pr = false;
  while (pr == false)
  {
    r = getRandom(0,UINT64_MAX);
    pr = isPrime(r,k);
  }
  latest_prime.collected = false;
  latest_prime.timeTaken = millis()-start;
  latest_prime.result.num = r;
  digitalWrite(LED_PIN,!digitalRead(LED_PIN));
}

void onReceive(int howMany)
{
  Serial.print("Received: ");
  Serial.println(howMany);
}

#if defined(ARDUINO_ARC32_TOOLS)
void handleUART()
{
  if (Serial1.available() > 0)
  {
    if (latest_prime.collected == false)
    {
      char num_str[21];
      Serial1.print(uintToStr(latest_prime.result.num,num_str));
      latest_prime.collected = true;
    }
    else
    {
      Serial1.print(zero_result);
    }
  }
}
#endif

void onRequest()
{
  if (latest_prime.collected == false)
  {
    char num_str[21];
    Wire.write(uintToStr(latest_prime.result.num,num_str));
    latest_prime.collected = true;
  }
  else
  {
  char num_str[21];
    Wire.write(uintToStr(zero_result,num_str));
  }
  Wire.endTransmission();
}

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); 

  // #if !defined(ARDUINO_AVR_NANO) && !defined(ARDUINO_ARC32_TOOLS)
  #if defined(ARDUINO_RASPBERRY_PI_PICO) || defined(ARDUINO_RASPBERRY_PI_PICO_W) || defined(ARDUINO_GENERIC_F401CCUX)
  Wire.setSDA(SDA_PIN);
  Wire.setSCL(SCL_PIN);
  #endif

  #if defined(ARDUINO_ARC32_TOOLS)
  Serial1.begin(9600);
  #elif defined(ARDUINO_ESP32_DEV)
  Wire.begin((uint8_t)ADDRESS,SDA_PIN,SCL_PIN,400000);
  Wire.onReceive(onReceive);
  Wire.onRequest(onRequest);
  #else
  Wire.begin(ADDRESS);
  Wire.onReceive(onReceive);
  Wire.onRequest(onRequest);
  #endif

  latest_prime.result.num = zero_result;
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
  #if defined(ARDUINO_RASPBERRY_PI_PICO) || defined(ARDUINO_RASPBERRY_PI_PICO_W) || defined(ARDUINO_GENERIC_F401CCUX) || defined(ARDUINO_ESP32_DEV)
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
}
