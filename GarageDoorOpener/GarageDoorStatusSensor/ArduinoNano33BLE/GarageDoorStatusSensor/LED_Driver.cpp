/*! \file     LED_Driver.cpp
 *  \brief    Driver interface implementation for a reed switch
 */

#include "LED_Driver.hpp"
#include <Arduino.h>             //digitalWrite(...)

// Anonymous namespace for constants
namespace
{
  // RGB LED's must be set high to turn off for arduino nano 33 BLE. See schematic
  const auto TURN_ON = LOW;
  const auto TURN_OFF = HIGH;
  // Power LED is opposite
  const auto TURN_ON_PWR = HIGH;
  const auto TURN_OFF_PWR = LOW;
}

void LED_Driver::init_LEDs()
{
  pinMode(LEDB, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDR, OUTPUT);
  pinMode(LED_PWR, OUTPUT);
}

void LED_Driver::turnOnAllLEDs()
{
  turnOnPowerLED();
  makeColor(LEDColors::White);
}

void LED_Driver::turnOffAllLEDs()
{
  turnOffPowerLED();
  turnOffRGBLEDs();
}

void LED_Driver::turnOnPowerLED()
{
  digitalWrite(LED_PWR, TURN_ON_PWR);
}

void LED_Driver::turnOffPowerLED()
{
  digitalWrite(LED_PWR, TURN_OFF_PWR);
}

void LED_Driver::makeColor(const LED_Driver::LEDColors color)
{
  // start by switching all colors off
  turnOffRGBLEDs();

  // Now turn on the necessary color combinations
  switch(color)
  {
    case LEDColors::Blue:
      digitalWrite(LEDB, TURN_ON);
      break;
    case LEDColors::Cyan:
      digitalWrite(LEDB, TURN_ON);
      digitalWrite(LEDG, TURN_ON);
      break;
    case LEDColors::Green:
      digitalWrite(LEDG, TURN_ON);
      break;
    case LEDColors::Magenta:
      digitalWrite(LEDB, TURN_ON);
      digitalWrite(LEDR, TURN_ON);
      break;
    case LEDColors::Red:
      digitalWrite(LEDR, TURN_ON);
      break;
    case LEDColors::White:
      digitalWrite(LEDB, TURN_ON);
      digitalWrite(LEDG, TURN_ON);
      digitalWrite(LEDR, TURN_ON);
      break;
    case LEDColors::Yellow:
      digitalWrite(LEDG, TURN_ON);
      digitalWrite(LEDR, TURN_ON);
      break;
    default:
      break;
  }
}

void LED_Driver::turnOffRGBLEDs()
{
  digitalWrite(LEDB, TURN_OFF);
  digitalWrite(LEDG, TURN_OFF);
  digitalWrite(LEDR, TURN_OFF);
}