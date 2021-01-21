/*! \file     HAL_GarageDoorStatusSensor.cpp
 *  \brief    Hardware Abstraction Layer interface implementation for a garage door status sensor
 */

#include "HAL_GarageDoorStatusSensor.hpp"

GarageDoorSensor GarageDoorSensor::garage_sensor;

GarageDoorSensor& GarageDoorSensor::getInstance()
{
  return garage_sensor;
}

bool GarageDoorSensor::init_garageDoorStatusSensor()
{
  m_mutex.lock();
  const bool INIT_RESULT =  m_driver.init_reedSwitch(REED_SWITCH_DIGITAL_PIN_NAME, REED_SWITCH_DIGITAL_PIN_MODE);
  m_mutex.unlock();
  return INIT_RESULT;
}

GarageDoorSensor::GarageDoorStatus GarageDoorSensor::get_status()
{
  m_mutex.lock();
  GarageDoorStatus current_state = GarageDoorStatus::GARAGE_OPENED;

  // read the reed swtich state
  const ReedSwitchDriver::ReedSwitchStatus REEDSWITCH_STATE = m_driver.get_reedSwitchState(REED_SWITCH_DIGITAL_PIN_NAME, REED_SWITCH_DIGITAL_PIN_MODE);

  switch(REEDSWITCH_STATE)
  {
    case ReedSwitchDriver::ReedSwitchStatus::REEDSWITCH_OPENED:
      current_state = GarageDoorStatus::GARAGE_OPENED;
      #ifdef DEBUG_GARAGE_SENSOR
        Serial.print("HAL Garage Sensor: Reed switch was OPENED == Garage Door Opened\n");
      #endif
      break;
    case ReedSwitchDriver::ReedSwitchStatus::REEDSWITCH_CLOSED:
      current_state = GarageDoorStatus::GARAGE_CLOSED;
      #ifdef DEBUG_GARAGE_SENSOR
        Serial.print("HAL Garage Sensor: Reed switch was CLOSED == Garage Door Closed\n");
      #endif
      break;
    default:
      break;
  }

  m_mutex.unlock();
  return current_state;
}