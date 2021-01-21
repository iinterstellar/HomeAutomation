/*! \file     GarageDoorStatusSensor.ino
 *  \brief    Main sketch implementation for the Garage Door Status Sensor running on an Arduino Nano 33 BLE board
 *  \details  This file contains the main implementation of the Garage Door Status Sensor. The sensor shall 
 *            check the status of a reed switch to determine whether the garage door status is opened or closed
 */

#include "HAL_GarageDoorStatusSensor.hpp"
#include "HAL_LED_LightShow.hpp"

//#define DEBUG_GARAGE_SENSOR

// Anonymous namespace for constants
namespace
{
  using namespace std::chrono_literals;
  const rtos::Kernel::Clock::duration_u32 ONE_SECOND = 1000 * 1ms;
  const rtos::Kernel::Clock::duration_u32 TWO_SECONDS = 1000 * 2ms;
}

/*! \fn       void setup()
 *  \brief    Main initialization activities completed here
 */
void setup() 
{
  // put your setup code here, to run once:
  #ifdef DEBUG_GARAGE_SENSOR
    Serial.begin(115200);
  #endif
  auto& garageDoorSensor = GarageDoorSensor::getInstance();
  auto& showmaster = LightShowController::getInstance();
  showmaster.init_LEDs();
  const bool INIT_SUCCEEDED = garageDoorSensor.init_garageDoorStatusSensor();
  while(!INIT_SUCCEEDED)
  {
    // Indicate error occurred in initialization
    showmaster.errorShow();
  }
  pinMode(D2, INPUT_PULLUP);
  showmaster.starUpShow();
  showmaster.turnOnLED(showmaster.POWER_LED);
}

/*! \fn       void loop()
 *  \brief    Main loop of the sketch
 *  \details  This function is treated like the idle task of our Mbed RTOS
 */
void loop() 
{
  static auto& garageDoorSensor = GarageDoorSensor::getInstance();
  static auto& showmaster = LightShowController::getInstance();
  static GarageDoorSensor::GarageDoorStatus last_sensor_status = GarageDoorSensor::GarageDoorStatus::GARAGE_CLOSED;

  // get our garage door sensor status
  const GarageDoorSensor::GarageDoorStatus SENSOR_STATUS = garageDoorSensor.get_status();
  if(SENSOR_STATUS != last_sensor_status)
  {
    // garage door status changed
    switch(SENSOR_STATUS)
    {
      case GarageDoorSensor::GarageDoorStatus::GARAGE_CLOSED:
        showmaster.turnOnLED(showmaster.CLOSED_LED);
        showmaster.turnOffLED(showmaster.OPEN_LED);
        #ifdef DEBUG_GARAGE_SENSOR
          Serial.print("Garage Closed == Turn on Blue LED\n\n");
        #endif
        break;
      case GarageDoorSensor::GarageDoorStatus::GARAGE_OPENED:
        showmaster.turnOnLED(showmaster.OPEN_LED);
        showmaster.turnOffLED(showmaster.CLOSED_LED);
        #ifdef DEBUG_GARAGE_SENSOR
          Serial.print("Garage Opened == Turn on Green LED\n\n");
        #endif
        break;
      default:
        break;
    }

    // update last status value
    last_sensor_status = SENSOR_STATUS;
  }

  rtos::ThisThread::sleep_for(ONE_SECOND);
}