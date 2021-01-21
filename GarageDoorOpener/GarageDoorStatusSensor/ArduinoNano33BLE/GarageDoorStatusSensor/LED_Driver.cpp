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

void LED_Driver::turnOnLED(const BoardLEDs LED_name)
{
  switch(LED_name)
  {
    case BoardLEDs::LED_B:
      digitalWrite(LEDB, TURN_ON);
      break;
    case BoardLEDs::LED_G:
      digitalWrite(LEDG, TURN_ON);
      break;
    case BoardLEDs::LED_R:
      digitalWrite(LEDR, TURN_ON);
      break;
    case BoardLEDs::LED_P:
      digitalWrite(LED_PWR, TURN_ON_PWR);
      break;
    default:
      break;
  }
}

void LED_Driver::turnOffLED(const BoardLEDs LED_name)
{
  switch(LED_name)
  {
    case BoardLEDs::LED_B:
      digitalWrite(LEDB, TURN_OFF);
      break;
    case BoardLEDs::LED_G:
      digitalWrite(LEDG, TURN_OFF);
      break;
    case BoardLEDs::LED_R:
      digitalWrite(LEDR, TURN_OFF);
      break;
    case BoardLEDs::LED_P:
      digitalWrite(LED_PWR, TURN_OFF_PWR);
      break;
    default:
      break;
  }
}

void LED_Driver::turnOnAllLEDs()
{
  digitalWrite(LEDB, TURN_ON);
  digitalWrite(LEDG, TURN_ON);
  digitalWrite(LEDR, TURN_ON);
  digitalWrite(LED_PWR, TURN_ON_PWR);
}

void LED_Driver::turnOffAllLEDs()
{
  digitalWrite(LEDB, TURN_OFF);
  digitalWrite(LEDG, TURN_OFF);
  digitalWrite(LEDR, TURN_OFF);
  digitalWrite(LED_PWR, TURN_OFF_PWR);
}

void LED_Driver::turnOnAllStatusLEDs()
{
  digitalWrite(LEDB, TURN_ON);
  digitalWrite(LEDG, TURN_ON);
  digitalWrite(LEDR, TURN_ON);
}

void LED_Driver::turnOffAllStatusLEDs()
{
  digitalWrite(LEDB, TURN_OFF);
  digitalWrite(LEDG, TURN_OFF);
  digitalWrite(LEDR, TURN_OFF);
}