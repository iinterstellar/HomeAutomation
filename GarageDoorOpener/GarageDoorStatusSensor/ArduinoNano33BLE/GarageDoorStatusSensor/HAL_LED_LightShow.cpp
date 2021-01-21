/*! \file     HAL_LED_LightShow.cpp
 *  \brief    Hardware Abstraction Layer interface implementation for on board LED light shows
 */
#include "HAL_LED_LightShow.hpp"

// Anonymous namespace for constants
namespace
{
  using namespace std::chrono_literals;
  const rtos::Kernel::Clock::duration_u32 ONE_SECOND = 1000 * 1ms;
  const rtos::Kernel::Clock::duration_u32 TWO_SECOND = 1000 * 2ms;
  const rtos::Kernel::Clock::duration_u32 STARTUPSHOW_DURATION = 10 * 1000 * 1ms;
}

LightShowController LightShowController::show_master;

LightShowController& LightShowController::getInstance()
{
  return show_master;
}

void LightShowController::init_LEDs()
{
  m_mutex.lock();
  m_driver.init_LEDs();
  m_mutex.unlock();
}

void LightShowController::turnOnLED(const LED_Driver::BoardLEDs LED_name)
{
  m_mutex.lock();
  m_driver.turnOnLED(LED_name);
  m_mutex.unlock();
}

void LightShowController::turnOffLED(const LED_Driver::BoardLEDs LED_name)
{
  m_mutex.lock();
  m_driver.turnOffLED(LED_name);
  m_mutex.unlock();
}

void LightShowController::starUpShow()
{
  m_mutex.lock();
  
  m_driver.turnOnAllLEDs();
  rtos::ThisThread::sleep_for(ONE_SECOND);

  m_driver.turnOffAllStatusLEDs();
  rtos::ThisThread::sleep_for(ONE_SECOND);

  m_driver.turnOnLED(ERROR_LED);
  m_driver.turnOffLED(OPEN_LED);
  m_driver.turnOffLED(CLOSED_LED);
  rtos::ThisThread::sleep_for(ONE_SECOND);

  m_driver.turnOffLED(ERROR_LED);
  m_driver.turnOnLED(OPEN_LED);
  m_driver.turnOffLED(CLOSED_LED);
  rtos::ThisThread::sleep_for(ONE_SECOND);

  m_driver.turnOnLED(ERROR_LED);
  m_driver.turnOnLED(OPEN_LED);
  m_driver.turnOffLED(CLOSED_LED);
  rtos::ThisThread::sleep_for(ONE_SECOND);

  m_driver.turnOffLED(ERROR_LED);
  m_driver.turnOffLED(OPEN_LED);
  m_driver.turnOnLED(CLOSED_LED);
  rtos::ThisThread::sleep_for(ONE_SECOND);

  m_driver.turnOnLED(ERROR_LED);
  m_driver.turnOffLED(OPEN_LED);
  m_driver.turnOnLED(CLOSED_LED);
  rtos::ThisThread::sleep_for(ONE_SECOND);

  m_driver.turnOffLED(ERROR_LED);
  m_driver.turnOnLED(OPEN_LED);
  m_driver.turnOnLED(CLOSED_LED);
  rtos::ThisThread::sleep_for(ONE_SECOND);

  m_driver.turnOnLED(ERROR_LED);
  m_driver.turnOnLED(OPEN_LED);
  m_driver.turnOnLED(CLOSED_LED);
  rtos::ThisThread::sleep_for(ONE_SECOND);

  m_driver.turnOffAllLEDs();
  rtos::ThisThread::sleep_for(ONE_SECOND);

  m_mutex.unlock();
}

void LightShowController::errorShow()
{
  static bool ERROR_LED_TOGGLE = true;

  m_mutex.lock();

  // toggle the error LED
  (ERROR_LED_TOGGLE) ? m_driver.turnOnLED(ERROR_LED) : m_driver.turnOffLED(ERROR_LED);
  ERROR_LED_TOGGLE = !ERROR_LED_TOGGLE;
  rtos::ThisThread::sleep_for(ONE_SECOND);

  m_mutex.unlock();
}