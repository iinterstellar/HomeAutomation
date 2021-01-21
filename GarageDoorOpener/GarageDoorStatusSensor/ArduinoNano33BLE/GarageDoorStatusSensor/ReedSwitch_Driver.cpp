/*! \file     ReedSwitch_Driver.cpp
 *  \brief    Driver interface implementation for a reed switch
 */

#include "ReedSwitch_Driver.hpp"
#include <Arduino.h>             //digitalRead(...)

bool ReedSwitchDriver::isDigitalPin(const int pin_name) const
{
  bool is_digital_pin = false;
  if(pin_name == D2
    ||  pin_name == D3
    ||  pin_name == D4
    ||  pin_name == D5
    ||  pin_name == D6
    ||  pin_name == D7
    ||  pin_name == D8
    ||  pin_name == D9
    ||  pin_name == D10
    ||  pin_name == D11
    ||  pin_name == D12
  )
  {
    is_digital_pin = true;
  }

  return is_digital_pin;
}

bool ReedSwitchDriver::isSupportedPinMode(const int pin_mode) const
{
  bool is_supported_pinmode = false;
  if(pin_mode == INPUT_PULLUP)
  {
    is_supported_pinmode = true;
  }

  return is_supported_pinmode;
}

bool ReedSwitchDriver::init_reedSwitch(const int pin_name, const int pin_mode)
{
  const bool INIT_STATUS_SUCCEEDED = isDigitalPin(pin_name) && isSupportedPinMode(pin_mode);

  if(INIT_STATUS_SUCCEEDED)
  {
    // setup digital pin according to parameters
    pinMode(pin_name, pin_name);
  }

  return INIT_STATUS_SUCCEEDED;
}

ReedSwitchDriver::ReedSwitchStatus ReedSwitchDriver::get_reedSwitchState(const int pin_name, const int pin_mode)
{
  ReedSwitchStatus current_state = ReedSwitchStatus::REEDSWITCH_OPENED;

  switch (pin_mode)
  {
    case INPUT_PULLUP:
    {
      // switch is set to active low
      const int PIN_STATUS = digitalRead(pin_name);
      if(PIN_STATUS == HIGH)
      {
        current_state = ReedSwitchStatus::REEDSWITCH_OPENED;
      }
      else if(PIN_STATUS == LOW)
      {
        current_state = ReedSwitchStatus::REEDSWITCH_CLOSED;
      }
      else
      {
        // SHOULD NEVER HAPPEN
      }
      break;
    }
    default:
      break;
  }

  return current_state;
}