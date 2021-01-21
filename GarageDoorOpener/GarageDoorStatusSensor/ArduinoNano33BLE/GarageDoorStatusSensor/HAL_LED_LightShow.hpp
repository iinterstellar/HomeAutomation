/*! \file     HAL_LED_LightShow.hpp
 *  \brief    Hardware Abstraction Layer interface for on board LED Light shows
 *  \details  Implemented as a singleton and is thread safe
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
     *  \brief    Turns on the specified LED
     *  \param[in]    LED_name    LED name 
     */
    void turnOnLED(const LED_Driver::BoardLEDs LED_name);

    /*! \fn       void turnOffLED()
     *  \brief    Turns off the specified LED
     *  \param[in]    LED_name    LED name 
     */
    void turnOffLED(const LED_Driver::BoardLEDs LED_name);

    /*! \fn       void starUpShow()
     *  \brief    Performs a startup LED light show
     *  \note     This function calls thread sleep for a total of 13 seconds before returning
     */
    void starUpShow();

    /*! \fn       void errorShow()
     *  \brief    Toggles the error LED on each call
     *  \note     This function calls thread sleep for one second before returning
     */
    void errorShow();
  
  public:
    const LED_Driver::BoardLEDs ERROR_LED = LED_Driver::BoardLEDs::LED_R;
    const LED_Driver::BoardLEDs OPEN_LED = LED_Driver::BoardLEDs::LED_G;
    const LED_Driver::BoardLEDs CLOSED_LED = LED_Driver::BoardLEDs::LED_B;
    const LED_Driver::BoardLEDs POWER_LED = LED_Driver::BoardLEDs::LED_P;

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