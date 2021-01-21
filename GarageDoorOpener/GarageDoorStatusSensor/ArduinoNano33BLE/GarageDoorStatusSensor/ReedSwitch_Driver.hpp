/*! \file     ReedSwitch_Driver.hpp
 *  \brief    Driver interface for a reed switch
 *  \details  Not thread safe on its own
 */
#ifndef REEDSWITCH_DRIVER_H
#define REEDSWITCH_DRIVER_H

class ReedSwitchDriver
{
  public:
    ReedSwitchDriver(ReedSwitchDriver &other) = delete;
    void operator=(const ReedSwitchDriver &) = delete;

    /*! \fn       ReedSwitchDriver()
     *  \brief    Default constructor
     */
    ReedSwitchDriver() = default;

    /*! \fn       ~ReedSwitchDriver()
     *  \brief    Default destructor
     */
    ~ReedSwitchDriver() = default;
  
    /*! \enum     ReedSwitchStatus
     *  \brief    Specifies the status of the reed switch
     */
    enum class ReedSwitchStatus
    {
        REEDSWITCH_OPENED,      /**< reed switch is opened */
        REEDSWITCH_CLOSED       /**< reed switch is closed */
    };

    /*! \fn       bool init_reedSwitch()
     *  \brief    Initializes the reed switch GPIO pin
     *  \param[in]    pin_name    Digital pin connected to reed switch
     *  \param[in]    pin_mode    Digital pin mode setting
     *  \return   Return true if initialization succeeded, else false
     */
    bool init_reedSwitch(const int pin_name, const int pin_mode);

    /*! \fn       ReedSwitchStatus get_reedSwitchState().
     *  \brief    Reads the reed switch's digital input pin and returns switch status
     *  \param[in]    pin_name    Digital pin connected to reed switch
     *  \param[in]    pin_mode    Digital pin mode setting
     *  \return   Returns the status of the reed switch
     */
    ReedSwitchStatus get_reedSwitchState(const int pin_name, const int pin_mode);
  
  private:
    /*! \fn         bool isDigitalPin(const int pin_name)
     *  \param[in]    pin_name    Pin to check against
     *  \return     Return true if param pin_name is a digital pin, else false
     */
    bool isDigitalPin(const int pin_name) const;

    /*! \fn       bool isSupportedPinMode(const PinName pin_name)
     *  \param[in]    pin_mode    Pin mode to check against
     *  \return   Return true if param pin_mode is a supported pin mode for the driver, else false
     */
    bool isSupportedPinMode(const int pin_mode) const;
};

#endif  //  REEDSWITCH_DRIVER_H