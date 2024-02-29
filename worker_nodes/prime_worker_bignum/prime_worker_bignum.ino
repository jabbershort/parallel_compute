#include <Wire.h>
#include "limits.h"
#include "math_functions.h"

#if defined(ARDUINO_AVR_NANO)
const char* boardname = "AVR NANO";
const int LED_PIN = LED_BUILTIN;
const int ADDRESS = 42;
const int loop_timeout = 5000;

#elif defined(ARDUINO_RASPBERRY_PI_PICO) || defined(ARDUINO_RASPBERRY_PI_PICO_W)
const char* boardname = "PICO";
const int LED_PIN = LED_BUILTIN;
const int ADDRESS = 43;
const int SDA_PIN = 20;
const int SCL_PIN = 21;
const int loop_timeout = 2000;

#elif defined(ARDUINO_ESP32_DEV)
const char* boardname = "ESP32_DEV";
const int LED_PIN = 2;
const int ADDRESS = 45;
const int SDA_PIN = 21; //need to check
const int SCL_PIN = 22; //need to check
const int loop_timeout = 2000;

#elif defined(ARDUINO_XIAO_ESP32C3)
const char* boardname = "XIAO_ESP32C3";
const int LED_PIN = 0;  
const int ADDRESS = 46;
const int loop_timeout = 2000;

#elif defined(ARDUINO_SEEED_XIAO_NRF52840_SENSE)
const char* boardname = "nRF52840_Sense";
const int LED_PIN = LED_BUILTIN;
const int ADDRESS = 47;
const int loop_timeout = 4000; //need to check

#elif defined(ARDUINO_ARC32_TOOLS)
const char* boardname = "TinyTILE";
const int LED_PIN = LED_BUILTIN;
const int RX_PIN = 0;
const int TX_PIN = 1;
const int loop_timeout = 5000;

#elif defined(ARDUINO_GENERIC_F401CCUX)
const char* boardname = "STM32F4XX";
const byte LED_PIN = PC13;
const int ADDRESS = 48;
const byte SDA_PIN = PB7;
const byte SCL_PIN = PB6;
const int loop_timeout = 1000; //need to check

#else
const char* boardname = "UNKNOWN BOARD";
const int LED_PIN = LED_BUILTIN;
const int ADDRESS = 0;
const int loop_timeout = 5000;
#endif

union prime{
  uint64_t num;
  byte uBytes[8];
};

struct result{
  BigNumber result;
  int timeTaken;
  char* board;
};

result latest_prime;

void printResult(result res)
{
  char num_str[21];
  Serial.print(res.board);
  Serial.print(": ");
  Serial.print(res.result);
  Serial.print(". Time taken: ");
  Serial.print(res.timeTaken);
  Serial.println("ms.");
}

void generate_prime()
{
  digitalWrite(LED_PIN, HIGH); 
  int start = millis();
  int k = 20;
  uint64_t r;
  bool pr = false;
  while (pr == false)
  {
    r = getRandom(0,UINT64_MAX);
    pr = isPrime(r,k);
  }
  latest_prime.timeTaken = millis()-start;
  latest_prime.result = r;
  digitalWrite(LED_PIN, LOW); 
}

void generate_big_prime()
{
  digitalWrite(LED_PIN, HIGH); 
  int start = millis();
  int k = 20;
  BigNumber r;
  bool pr = false;
  while (pr == false)
  {
    r = getRandom(15);
    pr = isPrime(r,k);
  }
  latest_prime.timeTaken = millis()-start;
  latest_prime.result = r;
  digitalWrite(LED_PIN, LOW); 
}


void setup() {
  Serial.begin(115200);
  BigNumber::begin();
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); 

  latest_prime.result = 0;
  latest_prime.timeTaken = 0;
  latest_prime.board = (char*)boardname;

  delay(5000);
  Serial.print("Starting device: ");
  Serial.print(boardname);
  Serial.println(".");
}

void loop() 
{
  Serial.println("Tick");
  generate_big_prime();
  printResult(latest_prime);
  latest_prime.result = 0;
  latest_prime.timeTaken = 0;
  
  // int num_digits = 15;
  // Serial.println(getRandom(num_digits));
  delay(100);
}
