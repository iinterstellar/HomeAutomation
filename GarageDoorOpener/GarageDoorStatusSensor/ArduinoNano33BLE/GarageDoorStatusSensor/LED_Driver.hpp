/*! \file     LED_Driver.hpp
 *  \brief    Driver interface for on board LEDs
 *  \details  Not thread safe on its own
 */
#ifndef LED_DRIVER_H
#define LED_DRIVER_H

class LED_Driver
{
  public:
    LED_Driver(LED_Driver &other) = delete;
    void operator=(const LED_Driver &) = delete;

    /*! \fn       LED_Driver()
     *  \brief    Default constructor
     */
    LED_Driver() = default;

    /*! \fn       ~LED_Driver()
     *  \brief    Default destructor
     */
    ~LED_Driver() = default;

    /*! \enum     BoardLEDs
     *  \brief    Specifies the available board LEDs for use
     */
    enum class BoardLEDs
    {
      LED_R,      /**< On board red LED */
      LED_B,      /**< On board blue LED */
      LED_G,      /**< On board green LED */
      LED_P       /**< On board power LED */
    };

    /*! \fn       void init_LEDs()
     *  \brief    Initializes the LED GPIO pins for output
     */
    void init_LEDs();

    /*! \fn       void turnOnLED()
     *  \brief    Turns on the specified LED
     *  \param[in]    LED_name    LED name 
     */
    void turnOnLED(const BoardLEDs LED_name);

    /*! \fn       void turnOffLED()
     *  \brief    Turns off the specified LED
     *  \param[in]    LED_name    LED name 
     */
    void turnOffLED(const BoardLEDs LED_name);

    /*! \fn       void turnOnAllLEDs()
     *  \brief    Turns on all LEDs
     */
    void turnOnAllLEDs();

    /*! \fn       void turnOffAllLEDs()
     *  \brief    Turns off all LEDs
     */
    void turnOffAllLEDs();

    /*! \fn       void turnOnAllStatusLEDs()
     *  \brief    Turns on all LEDs except LED_P power LED
     */
    void turnOnAllStatusLEDs();

    /*! \fn       void turnOffAllStatusLEDs()
     *  \brief    Turns off all LEDs except LED_P power LED
     */
    void turnOffAllStatusLEDs();
};

#endif  //  LED_DRIVER_H