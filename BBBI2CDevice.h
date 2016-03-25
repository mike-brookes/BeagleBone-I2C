//
//  BBBI2CDevice.h
//  BBBI2CDevice
//
//  Created by Michael Brookes on 05/10/2015.
//  Copyright © 2015 Michael Brookes. All rights reserved.
//

#ifndef BBBI2CDevice_h
#define BBBI2CDevice_h

#define unI2CDebug( x ) cerr << x //!< If this is defined as I2CDebug snd the source recompiled then debug data will be printed..

#define I2C_1 "/dev/i2c-1" //!< File Path for the i2c-1 bus.
#define I2C_2 "/dev/i2c-2" //!< File Path for the i2c-2 bus.

#include <fcntl.h>
#include <iostream>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

using namespace std;

/*!
 *  \brief     BBBI2CDevice provides low level access to I2C devices on the BeagleBone Black.
 *  \author    Michael Brookes
 *  \version   1.1
 *  \date      Oct-2015
 *  \copyright GNU Public License.
 */
class BBBI2CDevice {

public:

    /**
     \brief Please refer to the documention provided for your BeagleBone Black to ascertain which i2c bus to use.
     */
    enum I2CBus {
        I2C1 = 1, //!< Path = /dev/itc-1
                I2C2 = 2, //!< Path = /dev/itc-2
                I2C3 = 3,//!< Path = /dev/itc-3
    };

    /**
	 \fn Public function I2C_GetStatus( void ) const
	 \brief Returns the device status.
	 \param <void>
	 \return <int> I2C_Status
	 */
    int I2C_GetStatus( void ) const;

    /**
     \fn Public function I2C_GetFileHandle( void ) const
     \brief Returns the bus file handle.
     \param <void>
     \returns <int> I2C_FileHandle
     */
    int I2C_GetFileHandle( void ) const;

    /**
     \fn Public function I2C_GetDeviceAddress( void ) const
     \brief Returns the device address in decimal.
     \param <void>
     \returns <int> I2C_DeviceAddress
     */
    int I2C_GetDeviceAddress( void ) const;

    /**
     \fn Public function I2C_GetBusAddressPath( void ) const
     \brief Returns the bus file path.
     \param <void>
     \returns <char> I2C_BusAddressPath
     */
    const char *I2C_GetBusAddressPath( void ) const;

    /**
     \fn Public function I2C_GetValue( unsigned int I2C_RegAddress )
     \brief Reads and returns the value on the passed register.
     \param unsigned <int> I2C_RegAddress
     \return <short> RegisterValue (-1 = failure to retrieve the register value)
     */
    short I2C_GetValue( unsigned int I2C_RegAddress );

    /**
     \fn Public function I2C_SetValue( unsigned int I2C_RegValue )
     \brief Saves the value to be written to the register.
     \param unsigned <int> I2C_RegValue
     \return <void>
     */
    void I2C_SetValue( unsigned int I2C_RegValue );

    /**
     \fn Public function I2C_SetBusAddress( I2CBus I2C_BusAddress )
     \brief Sets the bus address, must be one of the I2CBus addresses. See the Enum I2CBus.
     \param <I2CBus> I2C_BussAddress
     \return <int> -1 failure to open the bus, 0 success
     */
    int I2C_SetBusAddress( I2CBus I2C_BusAddress );

    /**
     \fn Public function I2C_SetDeviceAddress( int I2C_DeviceAddress )
     \brief Saves the device address
     \param <int> I2C_DeviceAddress
     \return <int> 0 success
     */
    int I2C_SetDeviceAddress( int I2C_DeviceAddress );

    /*!
     \fn private function I2C_WriteToReg( int RegToWriteTo, int ValToWriteToReg )
     \brief Writes to the RegToWriteTo value.
     \param <int> RegToWriteTo (hex format), <int> ValToWriteToReg (hex format)
     \return <int> -1 = failure to open the bus, 0 = success
     */
    int I2C_WriteToReg( int RegToWriteTo, int ValToWriteToReg );

    /**
     \brief BBBI2CDevice : A low level control of I2C devices on the Beaglebone Black.
      - Assigns the device bus and the device I2C address.
      - Tests opening the bus and connecting to the device.
      - Handles the communication between the user and the I2C Device.
      \param  int I2C_DeviceAddress, I2CBus I2C_BusAddress
     */
    BBBI2CDevice( int I2C_DeviceAddress, I2CBus I2C_BusAddress );

protected:

    char I2C_TxBuffer[2]; //!< Contains the register address and the value to write.
    char I2C_Buffer[1]; //!< Contains the value to write to an open register.

    const char *I2C_BusAddressPath; //!< Path to the Bus (see defines)

    unsigned char I2C_RegValue; //!< The hex value of the register to write to.

    int I2C_DeviceAddress; //!< The hex value of this device.
    int I2C_FileHandle; //!< A handle to the i2c bus
    int I2C_Status; //!< Current status of the device.

    I2CBus I2C_BusAddress; //!< see enum I2CBus

    /**
     \fn private function I2C_Open( void )
     \brief Opens the bus on the BBB
     \param <void>
     \return <int> -1 failure to open the bus, 0 success.
     */
    int I2C_Open( void );

    /**
	 \fn private function I2C_Write( void )
	 \brief Writes to the this->I2C_RegValue set using I2C_SetValue
	 \param <void>
	 \return <int> 0 = failure to open the bus, 1 = success
	 */
    int I2C_Write( void );

    /**
     \fn private function I2C_ConnectToDevice( void )
     \brief Attempts to create a connection to the device address.
     \param <void>
     \return <int> -1 = failure to open the bus, 0 = success
     */
    int I2C_ConnectToDevice( void );
};

#endif /* BBBI2CDevice_h */
