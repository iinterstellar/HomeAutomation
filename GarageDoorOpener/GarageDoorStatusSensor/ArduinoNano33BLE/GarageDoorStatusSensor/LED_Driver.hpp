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

    /*! \fn       void init_LEDs()
     *  \brief    Initializes the LED GPIO pins for output
     */
    void init_LEDs();

    /*! \fn       void turnOnAllLEDs()
     *  \brief    Turns on all on board LEDs
     *  \note     By default the RGB LEDs are set to create the color white
     */
    void turnOnAllLEDs();

    /*! \fn       void turnOffAllLEDs()
     *  \brief    Turns off all on board LEDs
     */
    void turnOffAllLEDs();

    /*! \fn       void turnOnPowerLED()
     *  \brief    Turns on the on board power LED
     */
    void turnOnPowerLED();

    /*! \fn       void turnOffLED()
     *  \brief    Turns off the on board power LED
     */
    void turnOffPowerLED();

    /*! \enum     LEDColors
     *  \brief    Specifies possible color outputs using on board RGB LEDs (no PWM capability found for on board LEDs)
     */
    enum class LEDColors
    {
      Blue,
      Cyan,
      Green,
      Magenta,
      Red,
      White,
      Yellow
    };

    /*! \fn       void makeColor()
     *  \brief    Combines the corresponding RGB LEDs to create the passed color selection
     *  \param[in]    color       Color to make with RGB LEDs
     */
    void makeColor(const LEDColors color);
    
    /*! \fn       void turnOffRGBLED()
     *  \brief    Turns off the on board RGB LEDs
     */
    void turnOffRGBLEDs();
};

#endif  //  LED_DRIVER_H