/*! \file     HAL_LED_LightShow.cpp
 *  \brief    Hardware Abstraction Layer interface implementation for on board LED light shows
 */
#include "HAL_LED_LightShow.hpp"

// Anonymous namespace for constants
namespace
{
  using namespace std::chrono_literals;
  const rtos::Kernel::Clock::duration_u32 ONE_SECOND = 1000 * 1ms;
  const rtos::Kernel::Clock::duration_u32 HALF_A_SECOND = 500 * 1ms;
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

void LightShowController::turnOnPowerLED()
{
  m_mutex.lock();
  m_driver.turnOnPowerLED();
  m_mutex.unlock();
}

void LightShowController::turnOffPowerLED()
{
  m_mutex.lock();
  m_driver.turnOffPowerLED();
  m_mutex.unlock();
}

void LightShowController::setLEDStatus(const LED_Driver::LEDColors status)
{
  m_mutex.lock();
  m_driver.makeColor(status);
  m_mutex.unlock();
}

void LightShowController::turnOffStatusLEDs()
{
  m_mutex.lock();
  m_driver.turnOffRGBLEDs();
  m_mutex.unlock();
}

void LightShowController::starUpShow()
{
  m_mutex.lock();
  
  m_driver.turnOnAllLEDs();
  rtos::ThisThread::sleep_for(HALF_A_SECOND);

  m_driver.turnOffRGBLEDs();
  rtos::ThisThread::sleep_for(HALF_A_SECOND);

  m_driver.makeColor(LED_Driver::LEDColors::Red);
  rtos::ThisThread::sleep_for(HALF_A_SECOND);

  m_driver.makeColor(LED_Driver::LEDColors::Yellow);
  rtos::ThisThread::sleep_for(HALF_A_SECOND);

  m_driver.makeColor(LED_Driver::LEDColors::Green);
  rtos::ThisThread::sleep_for(HALF_A_SECOND);

  m_driver.makeColor(LED_Driver::LEDColors::Cyan);
  rtos::ThisThread::sleep_for(HALF_A_SECOND);

  m_driver.makeColor(LED_Driver::LEDColors::Blue);
  rtos::ThisThread::sleep_for(HALF_A_SECOND);

  m_driver.makeColor(LED_Driver::LEDColors::Magenta);
  rtos::ThisThread::sleep_for(HALF_A_SECOND);  

  m_driver.makeColor(LED_Driver::LEDColors::White);
  rtos::ThisThread::sleep_for(HALF_A_SECOND);

  m_driver.turnOffAllLEDs();
  rtos::ThisThread::sleep_for(HALF_A_SECOND);

  m_mutex.unlock();
}

void LightShowController::errorShow()
{
  static bool error_led_toggle_flag = true;

  m_mutex.lock();

  // toggle the error LED
  (error_led_toggle_flag) ? m_driver.makeColor(ERROR_STATUS) : m_driver.turnOffRGBLEDs();
  error_led_toggle_flag = !error_led_toggle_flag;
  rtos::ThisThread::sleep_for(ONE_SECOND);

  m_mutex.unlock();
}