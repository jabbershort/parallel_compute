#ifndef BOARD_PROPERTIES_H
#define BOARD_PROPERTIES_H

#if defined(ARDUINO_UNOWIFIR4)
const char* boardname = "Arduino UNO R4 WiFi";
const int LED_PIN = LED_BUILTIN;
const int ADDRESS = 41;
const int loop_timeout = 5000;

#elif defined(ARDUINO_AVR_NANO)
const char* boardname = "Arduino Nano";
const int LED_PIN = LED_BUILTIN;
const int ADDRESS = 42;
const int loop_timeout = 5000;

#elif defined(ARDUINO_RASPBERRY_PI_PICO) || defined(ARDUINO_RASPBERRY_PI_PICO_W)
const char* boardname = "Raspberry Pi Pico";
const int LED_PIN = LED_BUILTIN;
const int ADDRESS = 43;
const int SDA_PIN = 20;
const int SCL_PIN = 21;
const int loop_timeout = 2000;

#elif defined(ARDUINO_ESP32_DEV)
const char* boardname = "ESP32 Dev Board";
const int LED_PIN = 2;
const int ADDRESS = 45;
const int SDA_PIN = 21; //need to check
const int SCL_PIN = 22; //need to check
const int loop_timeout = 2000;

#elif defined(ARDUINO_XIAO_ESP32C3)
const char* boardname = "Seeed XIAO ESP32C3";
const int LED_PIN = 0;  
const int ADDRESS = 46;
const int loop_timeout = 2000;

#elif defined(ARDUINO_SEEED_XIAO_NRF52840_SENSE) 
// MBED PACKAGE BOARD
// #include "Adafruit_TinyUSB.h"
const char* boardname = "Seeed nRF52840 Sense";
const int LED_PIN = LED_BUILTIN;
const int ADDRESS = 47;
const int loop_timeout = 4000; //need to check

#elif defined(ARDUINO_Seeed_XIAO_nRF52840_Sense)
// NON MBED Package board
#include "Adafruit_TinyUSB.h"
const char* boardname = "Seeed nRF52840 Sense";
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
const char* boardname = "STM32F401CCUX";
const byte LED_PIN = PC13;
const int ADDRESS = 48;
const byte SDA_PIN = PB7;
const byte SCL_PIN = PB6;
const int loop_timeout = 1000; //need to check

#elif defined(ARDUINO_AVR_PROMICRO)
const char* boardname = "Pro Micro 32u4";
const int LED_PIN = LED_BUILTIN;
const int ADDRESS = 49;
const int loop_timeout = 5000;

#elif defined(ARDUINO_ESP8266_WEMOS_D1MINI)
const char* boardname = "D1 Mini ESP8266";
const int LED_PIN = LED_BUILTIN;
const int ADDRESS = 50;
const int loop_timeout = 5000;
  
#elif defined(ARDUINO_TEENSY40)
const char* boardname = "Teensy 4.0";
const int LED_PIN = LED_BUILTIN;
const int ADDRESS = 51;
const int loop_timeout = 5000;

#elif defined(ARDUINO_ITSYBITSY_M0)
const char* boardname = "ItsyBitsy M0";
const int LED_PIN = LED_BUILTIN;
const int ADDRESS = 52;
const int loop_timeout = 5000;

#elif defined(ARDUINO_ITSYBITSY_M4)
const char* boardname = "ItsyBitsy M4";
const int LED_PIN = LED_BUILTIN;
const int ADDRESS = 53;
const int loop_timeout = 5000;

#else
const char* boardname = "UNKNOWN BOARD";
const int LED_PIN = LED_BUILTIN;
const int ADDRESS = 0;
const int loop_timeout = 5000;
#endif

#endif