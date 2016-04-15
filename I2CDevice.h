//
// Created by Michael Brookes on 09/04/2016.
//

#ifndef I2CDEVICE_H
#define I2CDEVICE_H

#include "IDevice.h" //<!--Interface
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>

#define I2C_1 "/dev/i2c-1" //!< File Path for the i2c-1 bus.
#define I2C_2 "/dev/i2c-2" //!< File Path for the i2c-2 bus.
#define READ_LEN 1

namespace I2CDevice {
    using namespace std;

    class I2CDevice : public IDevice {

    public:
        ~I2CDevice( );
        I2CDevice( int _DeviceAddress, int _BusId );

        /*I2C Specific Members*/

        virtual int GetDeviceFileHandle( );
        virtual const char * GetFilePath( );
        virtual short GetValueFromRegister( unsigned char _RegisterValue );
        virtual void SetRegisterValue( unsigned char _RegisterValue );
        virtual void SetRegisterAddress( unsigned char _RegisterAddress );

    private:
        virtual struct I2CBus { const char * BusPath; } _Bus[ 2 ];

    protected:
        virtual void SetBusPaths( );
        virtual void SelectABusPath( int _BusId );
        virtual void SetDeviceAddress( int _DeviceAddress );

        /* From IDevice Interface*/
        virtual int ConnectToDevice( ) { return ioctl( this->FileHandle, I2C_SLAVE, this->DeviceAddress ); };
        virtual int OpenDevice( );
        virtual int WriteToDevice( size_t _BufferSize );
        virtual short ReadDevice( int _BufferSize );

        /*protected vars*/
        virtual const char * DeviceBusPath;

        virtual unsigned char RegisterValue;
        virtual unsigned char RegisterAddress;

        virtual int _Status;
        virtual int FileHandle;
        virtual int DeviceAddress;

        virtual short ReadValue;

        virtual char ReadAndWriteBuffer[ 2 ];
        virtual char WriteBufferOnly[ 1 ];
    };
}

#endif //I2CDEVICE_H
