/*! \file     GarageDoorStatusSensor.ino
 *  \brief    Main sketch implementation for the Garage Door Status Sensor running on an Arduino Nano 33 BLE board
 *  \details  This file contains the main implementation of the Garage Door Status Sensor. The sensor shall 
 *            check the status of a reed switch to determine whether the garage door status is opened or closed
 */

#include "HAL_GarageDoorStatusSensor.hpp"
#include "HAL_LED_LightShow.hpp"

#define DEBUG

// Anonymous namespace for constants
namespace
{
  using namespace std::chrono_literals;
  const rtos::Kernel::Clock::duration_u32 ONE_SECOND = 1000 * 1ms;
  const rtos::Kernel::Clock::duration_u32 TWO_SECONDS = 1000 * 2ms;
  #ifdef DEBUG
    const char SLEEP_MSG_TEMPLATE[] = "Deep sleep allowed: %i\r\n";
  #endif
}

/*! \fn       void setup()
 *  \brief    Main initialization activities completed here
 */
void setup() {
  // put your setup code here, to run once:
  #ifdef DEBUG
    Serial.begin(115200);
  #endif
  auto& garageDoorSensor = GarageDoorSensor::getInstance();
  auto& showmaster = LightShowController::getInstance();
  const bool INIT_SUCCEEDED = garageDoorSensor.init_garageDoorStatusSensor();
  while(!INIT_SUCCEEDED)
  {
    // Indicate error occurred in initialization
    showmaster.errorShow();
  }

  while(INIT_SUCCEEDED)
  {
    // Smooth operation. Sit here for now
    showmaster.starUpShow();
  }

  
}

/*! \fn       void loop()
 *  \brief    Main loop of the sketch
 *  \details  This function is treated like the idle task of our Mbed RTOS
 */
void loop() {
  #ifdef DEBUG
    static char sleep_msg[sizeof(SLEEP_MSG_TEMPLATE)] = { 0 };
  #endif

  // Unlock deep sleep
  sleep_manager_unlock_deep_sleep();
  #ifdef DEBUG
    Serial.print("Unlocking deep sleep\r\n");
    (void) sprintf(sleep_msg, SLEEP_MSG_TEMPLATE, sleep_manager_can_deep_sleep());
    Serial.print(sleep_msg);
  #endif

  // Deep sleep for 1 second
  rtos::ThisThread::sleep_for(ONE_SECOND);

  // Lock deep sleep
  sleep_manager_lock_deep_sleep();
  #ifdef DEBUG
    Serial.print("Locking deep sleep\r\n");
    (void) sprintf(sleep_msg, SLEEP_MSG_TEMPLATE, sleep_manager_can_deep_sleep());
    Serial.print(sleep_msg);
  #endif

  // Sleep for 1 second
  rtos::ThisThread::sleep_for(ONE_SECOND);
}