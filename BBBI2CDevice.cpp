//
//  BBBI2CDevice.cpp
//  BBBI2CDevice
//
//  Created by Michael Brookes on 05/10/2015.
//  Copyright � 2015 Michael Brookes. All rights reserved.
//
#include "BBBI2CDevice.h"

/**
 \brief BBBI2CDevice : A low level control of I2C devices on the Beaglebone Black.
  - Assigns the device bus and the device I2C address.
  - Tests opening the bus and connecting to the device.
  - Handles the communication between the user and the I2C Device.
  Empty Constructor - use I2C_Init after assigning the Bus and Device Address.
 */
BBBI2CDevice::BBBI2CDevice( int I2C_DeviceAddress, I2CBus I2C_BusAddress ) {

    if ( this->I2C_SetDeviceAddress( I2C_DeviceAddress ) < 0 )
        cerr << "BBBI2CDeviceError : Could not set the device address. The attempted value was : " << I2C_DeviceAddress << endl;

    if ( this->I2C_SetBusAddress( I2C_BusAddress ) < 0 )
        cerr << "BBBI2CDeviceError : Could not set the bus address. (The following number should be 1 or 2  : " << I2C_BusAddress << ")" << endl;

    if ( this->I2C_Open( ) < 0 )
        cerr << "BBBI2CDeviceError : Setting up file handle for I2C failed. (" << this->I2C_BusAddress << ")" << endl;

    if ( this->I2C_ConnectToDevice( ) < 0 )
        cerr << "BBBI2CDeviceError : Could not connect to I2C Address. (" << this->I2C_DeviceAddress << ")" << endl;

#ifdef I2CDebug
    I2CDebug( "BBBI2CDeviceDebug : New I2C Device - Setting Device Address to : " << I2C_DeviceAddress << endl );
    I2CDebug( "BBBI2CDeviceDebug : New I2C Device - Setting Bus Address to : " << I2C_BusAddress << endl );
    I2CDebug( "BBBI2CDeviceDebug : New I2C Device - Testing Opening The Device Bus : " << I2C_BusAddress << endl );
    I2CDebug( "This test assumes the LSM303DLHC accelerometer is attached...if that sensor is not attached this test will fail and provide misleading results..." << endl );
    I2CDebug( "BBBI2CDeviceDebug : " << " - Raw Sensor Data (0x2B @ 0x19 on i2c-1) = " << this->I2C_GetValue( 0x2B ) << endl );
    short _Y = ( ( short ) this->I2C_GetValue( 0x2B ) << 8 ) | ( short ) this->I2C_GetValue( 0x2A );
    I2CDebug( "The Y Value Obtained By Testing is : " << _Y << endl );
#endif

}

/**
 \fn private function I2C_Open( void )
 \brief Opens the bus on the BBB
 \param <void>
 \return <int> -1 failure to open the bus, 0 success.
 */
int BBBI2CDevice::I2C_Open( ) {
    this->I2C_FileHandle = open( this->I2C_BusAddressPath, O_RDWR );
    return this->I2C_FileHandle;
}

/**
 \fn private function I2C_Write( void )
 \brief Writes to the this->I2C_RegValue set using I2C_SetValue
 \param <void>
 \return <int> 0 = failure to open the bus, 1 = success
 */
int BBBI2CDevice::I2C_Write( void ) {
    this->I2C_Buffer[0] = this->I2C_RegValue;
    return write( this->I2C_FileHandle, this->I2C_Buffer, 1 );
}

/*!
 \fn private function I2C_WriteToReg( int RegToWriteTo, int ValToWriteToReg )
 \brief Writes to the RegToWriteTo value.
 \param <int> RegToWriteTo (hex format), <int> ValToWriteToReg (hex format)
 \return <int> -1 = failure to open the bus, 0 = success
 */
int BBBI2CDevice::I2C_WriteToReg( int RegToWriteTo, int ValToWriteToReg ) {
    this->I2C_TxBuffer[0] = RegToWriteTo;
    this->I2C_TxBuffer[1] = ValToWriteToReg;
    if ( write( this->I2C_FileHandle, this->I2C_TxBuffer, 2 ) != 2 )
        return -1;
    else
        return 0;
}

/**
 \fn private function I2C_ConnectToDevice( void )
 \brief Attempts to create a connection to the device address.
 \param <void>
 \return <int> -1 = failure to open the bus, 0 = success
 */
int BBBI2CDevice::I2C_ConnectToDevice( ) {
    return ioctl( this->I2C_FileHandle, I2C_SLAVE, this->I2C_DeviceAddress );
}

/**
 \fn private function I2C_GetStatus( void ) const
 \brief Returns the device status.
 \param <void>
 \return <int> I2C_Status
 */
int BBBI2CDevice::I2C_GetStatus( void ) const {
    return this->I2C_Status;
}

/**
  \fn private function I2C_GetFileHandle( void ) const
  \brief Returns the bus file handle.
  \param <void>
  \returns <int> I2C_FileHandle
  */
int BBBI2CDevice::I2C_GetFileHandle( void ) const {
    return this->I2C_FileHandle;
}

/**
 \fn private function I2C_GetDeviceAddress( void ) const
 \brief Returns the device address in decimal.
 \param <void>
 \returns <int> I2C_DeviceAddress
 */
int BBBI2CDevice::I2C_GetDeviceAddress( void ) const {
    return this->I2C_DeviceAddress;
}

/**
 \fn private function I2C_GetBusAddressPath( void ) const
 \brief Returns the bus file path.
 \param <void>
 \returns <char> I2C_BusAddressPath
 */
const char* BBBI2CDevice::I2C_GetBusAddressPath( void ) const {
    return this->I2C_BusAddressPath;
}

/**
 \fn private function I2C_GetValue( unsigned int I2C_RegAddress )
 \brief Reads and returns the value on the passed register.
 \param unsigned <int> I2C_RegAddress
 \return <short> RegisterValue (-1 = failure to retrieve the register value)
 */
short BBBI2CDevice::I2C_GetValue( unsigned int I2C_RegAddress ) {
    this->I2C_SetValue( I2C_RegAddress );
    if( this->I2C_Write( ) == 1 ) {
        unsigned char buff[1];
        if ( read( this->I2C_FileHandle, buff, 1 ) != 1 )
            return -1;
        else
            return buff[0];
    }
    else
        return -1;
}

/**
 \fn private function I2C_SetValue( unsigned int I2C_RegValue )
 \brief Saves the value to be written to the register.
 \param unsigned <int> I2C_RegValue
 \return <void>
 */
void BBBI2CDevice::I2C_SetValue( unsigned int I2C_RegValue ) {
    this->I2C_RegValue = I2C_RegValue;
}

/**
 \fn private function I2C_SetBusAddress( I2CBus I2C_BusAddress )
 \brief Sets the bus address, must be one of the I2CBus addresses. See the Enum I2CBus.
 \param <I2CBus> I2C_BussAddress
 \return <int> -1 failure to open the bus, 0 success
 */
int BBBI2CDevice::I2C_SetBusAddress( I2CBus I2C_BusAddress ) {
    if ( I2C_BusAddress == this->I2C1 )
        this->I2C_BusAddressPath = I2C_1;
    else if ( I2C_BusAddress == this->I2C2 )
        this->I2C_BusAddressPath = I2C_2;
    else
        return -1; //error
    return 0; //success
}

/**
 \fn private function I2C_SetDeviceAddress( int I2C_DeviceAddress )
 \brief Saves the device address
 \param <int> I2C_DeviceAddress
 \return <int> 0 success
 */
int BBBI2CDevice::I2C_SetDeviceAddress( int I2C_DeviceAddress ) {
    this->I2C_DeviceAddress = I2C_DeviceAddress;
    return 0;
}
