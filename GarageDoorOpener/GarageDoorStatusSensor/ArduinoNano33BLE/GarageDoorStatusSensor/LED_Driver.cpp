/*! \file     LED_Driver.cpp
 *  \brief    Driver interface implementation for a reed switch
 */

#include "LED_Driver.hpp"
#include <Arduino.h>             //digitalWrite(...)

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
      digitalWrite(LEDB, HIGH);
      break;
    case BoardLEDs::LED_G:
      digitalWrite(LEDG, HIGH);
      break;
    case BoardLEDs::LED_R:
      digitalWrite(LEDR, HIGH);
      break;
    case BoardLEDs::LED_P:
      digitalWrite(LED_PWR, HIGH);
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
      digitalWrite(LEDB, LOW);
      break;
    case BoardLEDs::LED_G:
      digitalWrite(LEDG, LOW);
      break;
    case BoardLEDs::LED_R:
      digitalWrite(LEDR, LOW);
      break;
    case BoardLEDs::LED_P:
      digitalWrite(LED_PWR, LOW);
      break;
    default:
      break;
  }
}

void LED_Driver::turnOnAllLEDs()
{
  digitalWrite(LEDB, HIGH);
  digitalWrite(LEDG, HIGH);
  digitalWrite(LEDR, HIGH);
  digitalWrite(LED_PWR, HIGH);
}

void LED_Driver::turnOffAllLEDs()
{
  digitalWrite(LEDB, LOW);
  digitalWrite(LEDG, LOW);
  digitalWrite(LEDR, LOW);
  digitalWrite(LED_PWR, LOW);
}

void LED_Driver::turnOnAllStatusLEDs()
{
  digitalWrite(LEDB, HIGH);
  digitalWrite(LEDG, HIGH);
  digitalWrite(LEDR, HIGH);
}

void LED_Driver::turnOffAllStatusLEDs()
{
  digitalWrite(LEDB, LOW);
  digitalWrite(LEDG, LOW);
  digitalWrite(LEDR, LOW);
}