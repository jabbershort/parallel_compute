#ifndef BOARD_PROPERTIES_H
#define BOARD_PROPERTIES_H

#if defined(ARDUINO_UNOWIFIR4)
const char* boardname = "Arduino UNO R4 WiFi";
const char* processorname = "Renesas RA4M1";
const char* corename = "Arm Cortex-M4";
const int LED_PIN = LED_BUILTIN;
const int ADDRESS = 41;

#elif defined(ARDUINO_AVR_NANO)
const char* boardname = "Arduino Nano";
const char* processorname = "ATMega 328p";
const char* corename = "AVR RISC";
const int LED_PIN = LED_BUILTIN;
const int ADDRESS = 42;

#elif defined(ARDUINO_RASPBERRY_PI_PICO) || defined(ARDUINO_RASPBERRY_PI_PICO_W)
const char* boardname = "Raspberry Pi Pico";
const char* processorname = "RP2040";
const char* corename = "Dual Arm Cortex-M0+";
const int LED_PIN = LED_BUILTIN;
const int ADDRESS = 43;
const int SDA_PIN = 20;
const int SCL_PIN = 21;

#elif defined(ARDUINO_ESP32_DEV)
const char* boardname = "ESP32 Dev Board";
const char* processorname = "Tensilica Xtensa";
const char* corename = "LX6";
const int LED_PIN = 2;
const int ADDRESS = 45;
const int SDA_PIN = 21; 
const int SCL_PIN = 22; 

#elif defined(ARDUINO_XIAO_ESP32C3)
const char* boardname = "Seeed XIAO ESP 32C3";
const char* processorname = "ESP32-C3";
const char* corename = "RISC-V";

const int LED_PIN = 0;  
const int ADDRESS = 46;

#elif defined(ARDUINO_SEEED_XIAO_NRF52840_SENSE) 
// MBED PACKAGE BOARD
// MBED PACKAGE BOARD
const char* boardname = "Seeed nRF52840 Sense";
const char* processorname = "nRF52840";
const char* corename = "Arm Cortex-M4";
const int LED_PIN = LED_BUILTIN;
const int ADDRESS = 47;

#elif defined(ARDUINO_Seeed_XIAO_nRF52840_Sense)
// NON MBED Package board
#include "Adafruit_TinyUSB.h"
const char* boardname = "Seeed nRF52840 Sense";
const char* processorname = "nRF52840";
const char* corename = "Arm Cortex-M4";
const int LED_PIN = LED_BUILTIN;
const int ADDRESS = 47;

#elif defined(ARDUINO_ARC32_TOOLS)
const char* boardname = "TinyTILE";
const char* processorname = "Intel Curie";
const char* corename = "Intel Quark (x86) and ARC";
const int LED_PIN = LED_BUILTIN;
const int RX_PIN = 0;
const int TX_PIN = 1;

#elif defined(ARDUINO_GENERIC_F401CCUX)
const char* boardname = "STM32F4XX Clone";
const char* processorname = "STM32F401CCUX";
const char* corename = "Arm Cortex-M4";
const byte LED_PIN = PC13;
const int ADDRESS = 48;
const byte SDA_PIN = PB7;
const byte SCL_PIN = PB6;

#elif defined(ARDUINO_AVR_PROMICRO)
const char* boardname = "Pro Micro 32u4";
const char* processorname = "ATMega 32u4";
const char* corename = "AVR RISC";
const int LED_PIN = LED_BUILTIN;
const int ADDRESS = 49;

#elif defined(ARDUINO_ESP8266_WEMOS_D1MINI)
const char* boardname = "D1 Mini ESP8266";
const char* processorname = "Tensilica";
const char* corename = " L106";
const int LED_PIN = LED_BUILTIN;
const int ADDRESS = 50;
  
#elif defined(ARDUINO_TEENSY40)
const char* boardname = "Teensy 4.0";
const char* processorname = "NXP iMXRT1062";
const char* corename = "Arm Cortex-M7";
const int LED_PIN = LED_BUILTIN;
const int ADDRESS = 51;

#elif defined(ARDUINO_ITSYBITSY_M0)
const char* boardname = "ItsyBitsy M0";
const char* processorname = "SAMD21";
const char* corename = "Arm Cortex-M0+";
const int LED_PIN = LED_BUILTIN;
const int ADDRESS = 52;

#elif defined(ARDUINO_ITSYBITSY_M4)
const char* boardname = "ItsyBitsy M4";
const char* processorname = "SAMD51";
const char* corename = "Arm Cortex-M4";
const int LED_PIN = LED_BUILTIN;
const int ADDRESS = 53;

#elif defined(ARDUINO_MINIMA)
//https://forum.arduino.cc/t/weact-studio-64pin-ra4m1-uno-r4-minima-clone-pin-mapping/1202932
const char* boardname = "Arduino R4 Minima (Clone)";
const char* processorname = "Renesas RA4M1";
const char* corename = "Arm Cortex-M4";
const int LED_PIN = 21;
const int ADDRESS = 54;

#elif defined(ARDUINO_GENERIC_G474CETX)
const char* boardname = "STM32G474CEU6";
const char* processorname = "STM32G474CEU6";
const char* corename = "Arm Cortex-M4";
const int LED_PIN = 0;
const int SDA_PIN = 8;
const int SCL_PIN = 9;
const int ADDRESS = 55;

#elif defined(ARDUINO_GENERIC_F103RCTX)
///swd programmer using st link
const char* boardname = "STM32F103RCT6";
const char* processorname =  "STM32F103RCT6";
const char* corename = "Arm Cortex M3";
const byte LED_PIN = PC13;
const byte SDA_PIN = PB7;
const byte SCL_PIN = PB6;
const int ADDRESS = 56;

#elif defined(ARDUINO_GENERIC_F103C8TX)
/// swd programmer using st link 
const char* boardname = "STM32F103C8T6";
const char* processorname = "STM32F103C8T6";
const char* corename = "Arm Cortex M3";
const byte LED_PIN = PC13;
const byte SDA_PIN = PB7;
const byte SCL_PIN = PB6;
const int ADDRESS = 57;

#else
const char* boardname = "UNKNOWN BOARD";
const int LED_PIN = LED_BUILTIN;
const int ADDRESS = 0;
const int loop_timeout = 5000;
#endif
#endif