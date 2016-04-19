//
// Created by Michael Brookes on 09/04/2016.
//

#ifndef I2CDEVICE_H
#define I2CDEVICE_H

#include "IDevice.h" //<!--Interface
#include "ExceptionAid.h"
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>

#define I2C_BUS_COUNT   2               //!< How many I2C buses are available. Add paths below as required.
#define I2C_1           "/dev/i2c-1"    //!< File Path for the i2c-1 bus.
#define I2C_2           "/dev/i2c-2"    //!< File Path for the i2c-2 bus.

#define ONE_BYTE        1               //!< Used for specifying how many bytes to read
#define TWO_BYTES       2               //!< Used for specifying how many bytes to write

namespace I2CDevice {
    using namespace std;

    class I2CDevice : public IDevice {

    public:
        /**
         \fn Public Destructor
         */
        ~I2CDevice( );

        /**
         \fn Public Constructor
         \param int _DeviceAddress = Hex address value for the I2C device.
         \param int _BusId = the I2C Bus no. that the I2C device is plugged into.
         */
        I2CDevice( int _DeviceAddress, int _BusId ) throw( exception& );

        /*I2C Specific Members*/

        /**
         \fn Public GetDeviceHandle
         \param none
         \brief Returns the current FileHandle for reading and writing to the I2C device.
         */
        virtual int GetDeviceFileHandle( );

        /**
         \fn Public GetFilePath
         \param none
         \brief Returns then FilePath for accessing the I2C device.
         */
        virtual const char * GetFilePath( );

        /**
         \fn Public GetValueFromRegister
         \param unsigned char _RegisterValue
         \brief Writes the register that you want to read, then performs a read on that register.
         */
        virtual short GetValueFromRegister( unsigned char _RegisterValue );

        /**
         \fn Public SetRegisterValue
         \param unsigned char _RegisterValue
         \brief Set the value that will next be written to the I2C device.
         */
        virtual void SetRegisterValue( unsigned char _RegisterValue );

        /**
         \fn Public SetRegisterAddress
         \param unsigned char _RegisterAddress
         \brief Set the Register address that the _RegisterValue will be written to.
         */
        virtual void SetRegisterAddress( unsigned char _RegisterAddress );

        /**
         \fn Public WriteToDevice
         \param size_t _BufferSize
         \brief Perform the write request. The _BufferSize is used to differentiate between a read or write request.
         */
        virtual int WriteToDevice( size_t _BufferSize );

    private:

        /**
         \fn Private Struct I2CBus
         \brief
         */
        virtual struct I2CBus { const char * BusPath; } _Bus[ I2C_BUS_COUNT ];

    protected:

        /**
         \fn Protected SetBusPaths
         \param none
         \brief Set Path to all the available buses. As set with I2CBus and Defines.
         */
        virtual void SetBusPaths( );

        /**
         \fn Protected ValidateBusId
         \param int _BusId
         \brief Make sure the BusId being used is valid.
         */
        virtual int ValidateBusId( int _BusId );

        /**
         \fn Protected SelectABusPath
         \param none
         \brief Select which Bus Path we can find your I2C device at.
         */
        virtual void SelectABusPath( I2CBus _I2CBus );

        /**
         \fn Protected SetDeviceAddress
         \param int _DeviceAddress
         \brief Used to store the device address (Hex)
         */
        virtual void SetDeviceAddress( int _DeviceAddress );

        /* From IDevice Interface*/

        /**
         \fn Protected ConnectToDevice
         \param none
         \brief Sets up an IOCTL connection to the I2C device as a Slave for Linux.
         */
        virtual int ConnectToDevice( ) { return ioctl( this->FileHandle, I2C_SLAVE, this->DeviceAddress ); };

        /**
         \fn Protected OpenDevice
         \param none
         \brief Attempt to open the FileHandle.
         */
        virtual int OpenDevice( );

        /**
         \fn Protected ReadDevice
         \param size_t _BufferSize
         \brief Reads the current buffer from the I2C device - first writes the register address that will be read.
         */
        virtual short ReadDevice( size_t _BufferSize );

        virtual const char * DeviceBusPath;

        virtual unsigned char RegisterValue;
        virtual unsigned char RegisterAddress;

        virtual int FileHandle;
        virtual int DeviceAddress;
        virtual int BusId;

        virtual char ReadAndWriteBuffer[ TWO_BYTES ];
        virtual char WriteBufferOnly[ ONE_BYTE ];

    };
}

#endif //I2CDEVICE_H
