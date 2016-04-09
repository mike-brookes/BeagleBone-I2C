//
// Created by Michael Brookes on 09/04/2016.
//

#ifndef IDEVICE_H
#define IDEVICE_H

#include <bits/fcntl-linux.h>
#include <fcntl.h>

namespace IDevice {

    class IDevice {

        public:
            virtual ~IDevice( ) = 0;
            virtual int GetDeviceAddress( ) { return this->_DeviceAddress; }
            virtual int GetFileHandle( ) { return this->_DeviceFH; }
            virtual const char * GetFilePath( ) { return this->_FilePath; }

        private:
            virtual void SetDeviceAddress( int _DeviceAddress ) { this->_DeviceAddress = _DeviceAddress; };
            virtual void SetFileHandle( int _DeviceFH ) { this->_DeviceFH = _DeviceFH; };
            virtual void SetFilePath( const char * _FilePath ) {  };
            virtual int WriteToDevice( ) = 0;
            virtual int ReadDevice( ) = 0;
            virtual int OpenDevice( ) { return open( this->_FilePath, O_RDWR ); };
            virtual int ConnectToDevice( ) = 0;

            virtual int _DeviceAddress;
            virtual int _DeviceFH;
            const char *_FilePath;

        protected:
            IDevice( );

    };

}
#endif //IDEVICE_H