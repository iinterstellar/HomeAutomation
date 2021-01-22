/*! \file     HAL_LED_LightShow.hpp
 *  \brief    Hardware Abstraction Layer interface for on board LED Light shows
 *  \details  Implemented as a singleton and is thread safe. All things "on board LED" happen through this interface
 */
#ifndef HAL_LED_LIGHTSHOW_H
#define HAL_LED_LIGHTSHOW_H
  
#include <Arduino.h>  // Mutex
#include "LED_Driver.hpp"

class LightShowController
{
  public:
    /*!
     * Singletons should not be cloneable.
     */
    LightShowController(LightShowController &other) = delete;

    /*!
     * Singletons should not be assignable.
     */
    void operator=(const LightShowController &) = delete;

    /*! \fn       ~GarageDoorSensor()
     *  \brief    Default destructor
     */
    ~LightShowController() = default;

    /*! \fn       static LightShowController& getInstance()
     *  \return   Returns an instance of the LightShowController singleton object
     */
    static LightShowController& getInstance();

    /*! \fn       void init_LEDs()
     *  \brief    Initializes LEDs for output
     */
    void init_LEDs();

    /*! \fn       void turnOnLED()
     *  \brief    Turns on the on board power LED
     */
    void turnOnPowerLED();

    /*! \fn       void turnOffLED()
     *  \brief    Turns off on board power LED
     */
    void turnOffPowerLED();

    /*! \fn       void setLEDStatus(const LED_Driver::LEDColors status)
     *  \brief    Sets the on board RGB LED to indicate the passed color status
     *  \param[in]    status      LED color status to display on the on board RGB LEDs
     */
    void setLEDStatus(const LED_Driver::LEDColors status);

    /*! \fn       void turnOffLED()
     *  \brief    Turns off the on status LEDs (the RGB LEDs)
     */
    void turnOffStatusLEDs();

    /*! \fn       void starUpShow()
     *  \brief    Performs a startup LED light show
     *  \note     This function calls thread sleep for a combined total of 5 seconds before returning
     */
    void starUpShow();

    /*! \fn       void errorShow()
     *  \brief    Toggles the error LED on each call
     *  \note     This function calls thread sleep for one second before returning
     */
    void errorShow();
  
  public:
    // Note these LED status indicators all use the same on board RGB LED, so only one status can be displayed at a time
    const LED_Driver::LEDColors ERROR_STATUS = LED_Driver::LEDColors::Red;
    const LED_Driver::LEDColors GARAGE_OPENED_STATUS = LED_Driver::LEDColors::Green;
    const LED_Driver::LEDColors GARAGE_CLOSED_STATUS = LED_Driver::LEDColors::Blue;

  private:
    /*! \fn       LightShowController()
     *  \brief    Private constructor as this class is not meant to be instantiated directly
     */
    LightShowController() = default;

    static LightShowController show_master;
    rtos::Mutex m_mutex;
    LED_Driver m_driver;
};

#endif  //  HAL_LED_LIGHTSHOW_H