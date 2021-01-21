/*! \file     HAL_GarageDoorStatusSensor.hpp
 *  \brief    Hardware Abstraction Layer interface for a garage door status sensor
 *  \details  Implemented as a singleton and is thread safe
 */
#ifndef HAL_GARAGEDOORSTATUSSENSOR_H
#define HAL_GARAGEDOORSTATUSSENSOR_H
  
#include <Arduino.h>  // Mutex, REED_SWITCH_DIGITAL_PIN_NAME, REED_SWITCH_DIGITAL_PIN_MODE
#include "ReedSwitch_Driver.hpp"

// setup pins in use here
#define REED_SWITCH_DIGITAL_PIN_NAME    D2
#define REED_SWITCH_DIGITAL_PIN_MODE    INPUT_PULLUP

class GarageDoorSensor
{
  public:
    /*!
     * Singletons should not be cloneable.
     */
    GarageDoorSensor(GarageDoorSensor &other) = delete;

    /*!
     * Singletons should not be assignable.
     */
    void operator=(const GarageDoorSensor &) = delete;

    /*! \fn       ~GarageDoorSensor()
     *  \brief    Default destructor
     */
    ~GarageDoorSensor() = default;

    /*! \enum     GarageDoorStatus
     *  \brief    Specifies the status of the garage door
     */
    enum class GarageDoorStatus
    {
      GARAGE_OPENED,        /**< garage door is opened */
      GARAGE_CLOSED         /**< garage door is closed */
    };

    /*! \fn       bool init_garageDoorStatusSensor()
     *  \brief    Initializes the garage door status sensor hardware
     *  \return   Return true if initialization succeeded, else false
     */
    bool init_garageDoorStatusSensor();

    /*! \fn       GarageDoorStatus get_status()
     *  \return   Returns the status of the garage door sensor
     */
    GarageDoorStatus get_status();

    /*! \fn       static GarageDoorSensor& getInstance()
     *  \return   Returns an instance of the GarageDoorSensor singleton object
     */
    static GarageDoorSensor& getInstance();

  private:
    /*! \fn       GarageDoorSensor()
     *  \brief    Private constructor as this class is not meant to be instantiated directly
     */
    GarageDoorSensor() = default;

    static GarageDoorSensor garage_sensor;
    rtos::Mutex m_mutex;
    ReedSwitchDriver m_driver;
};

#endif  //  HAL_GARAGEDOORSTATUSSENSOR_H