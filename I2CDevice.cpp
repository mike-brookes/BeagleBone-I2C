//
// Created by Michael Brookes on 14/04/2016.
//

#include "I2CDevice.h"

namespace I2C {

    I2CDevice::I2CDevice( int _DeviceAddress, int _BusId ) throw( I2CSetupException& ) {

        /*
         * ** ## -- Setup Stage -- ## ** *
         * SetBusPaths : Saves the file paths to the available buses for ease of access.
         */
        this->SetBusPaths( );

        /*
         * ** ## -- Assignment Stage ( based on args ) -- ## ** *
         * ValidateBusId : Make sure we have a valid bus ID before proceeding.
         * SelectABusPath : Used to specify which bus your I2C device is on.
         * SetDeviceAddress: Hex value for your specific I2C Device.
         */
        this->ValidateBusId( _BusId );
        this->SelectABusPath( this->_Bus[ _BusId ] );
        this->SetDeviceAddress( _DeviceAddress );

        /*
         * ** ## -- Init Stage -- ## ** *
         * OpenDevice : Creates a file handle for the device, should it be closed? Probably... :)
         * ConnectToDevice : Assigns the device as an I2C Slave and checks availability using IOCTL
         *
         * More info on IOCTL : http://man7.org/linux/man-pages/man2/ioctl.2.html
         */
        this->OpenDevice( );
        this->ConnectToDevice( );

    }

    I2CDevice::~I2CDevice( ) { close( this->FileHandle ); }

    void I2CDevice::SetBusPaths( ) {
        this->_Bus[ 1 ].BusPath = this->ValidateBusPath( (char *)I2C_1 );
    }

    void I2CDevice::SelectABusPath( I2CBus _I2CBus ) { this->DeviceBusPath = _I2CBus.BusPath; }

    void I2CDevice::SetRegisterValue( unsigned char _RegisterValue ){ this->RegisterValue = _RegisterValue; }

    void I2CDevice::SetRegisterAddress( unsigned char _RegisterAddress ){ this->RegisterAddress = _RegisterAddress; }

    void I2CDevice::SetDeviceAddress( int _DeviceAddress ) { this->DeviceAddress = _DeviceAddress; }

    const char * I2CDevice::GetFilePath( ) { return this->DeviceBusPath; }

    int I2CDevice::GetDeviceFileHandle( ) { return this->FileHandle; }

    int I2CDevice::ValidateBusId( int _BusId ) throw( I2CSetupException& ) {
        this->BusId = _BusId;
        if( this->BusId > I2C_BUS_COUNT || this->BusId < 1 ) {
            snprintf( this->ErrMessage, sizeof( this->ErrMessage ), "Bus ID : %d  is not a valid BUS for this device.", _BusId );
            throw( I2CSetupException( this->ErrMessage ) );
        }
        else
            return EXIT_SUCCESS;
    }

    char * I2CDevice::ValidateBusPath( char * _I2CBusProposedPath ) throw( I2CSetupException& ) {
        if( stat ( _I2CBusProposedPath, &buffer) == 0 )
            return _I2CBusProposedPath;
        else{
            snprintf( this->ErrMessage, sizeof( this->ErrMessage ), "Fatal I2C Error - Unable to locate the I2C Bus file : %s", _I2CBusProposedPath );
            throw I2CSetupException( this->ErrMessage );
        }
    }

    short I2CDevice::GetValueFromRegister( unsigned char _RegisterAddress ) {
        this->SetRegisterAddress( _RegisterAddress );
        this->WriteBufferOnly[ 0 ] = this->RegisterAddress;
        if( write( this->GetDeviceFileHandle( ), this->WriteBufferOnly, 1 ) == 1 ) {
            return this->ReadDevice( ONE_BYTE );
        }
        else {
            snprintf( this->ErrMessage, sizeof( this->ErrMessage ), "Fatal I2C Error - Unable to write to file : %s", this->GetFilePath( ));
            throw I2CSetupException( this->ErrMessage );
        }
    }

    short I2CDevice::ReadDevice( size_t _BufferSize ) throw( I2CSetupException& ) {
        unsigned char buff[ _BufferSize ];
        if( read( this->GetDeviceFileHandle( ), buff, _BufferSize ) != _BufferSize ) {
            snprintf( this->ErrMessage, sizeof( this->ErrMessage ), "Fatal I2C Error - Unable to read from file : %s", this->GetFilePath( ) );
            throw I2CSetupException( this->ErrMessage );
        }
        else
            return buff[ 0 ];
    }

    int I2CDevice::OpenDevice( ) throw( I2CSetupException& ) {
        this->FileHandle = open( this->GetFilePath( ), O_RDWR );
        if( this->FileHandle == 0 ) {
            snprintf( this->ErrMessage, sizeof( this->ErrMessage ), "Fatal I2C Error - Unable to open file : %s", this->GetFilePath( ) );
            throw I2CSetupException( this->ErrMessage );
        }
        return this->FileHandle;
    }

    int I2CDevice::WriteToDevice( size_t _BufferSize  ) throw( I2CSetupException& ) {
        try {
            if( _BufferSize > ONE_BYTE ) {
                this->ReadAndWriteBuffer[ 0 ] = this->RegisterAddress;
                this->ReadAndWriteBuffer[ 1 ] = this->RegisterValue;
                write( this->GetDeviceFileHandle( ), this->ReadAndWriteBuffer, _BufferSize );
            }
            else {
                this->WriteBufferOnly[ 0 ] = this->RegisterAddress;
                write( this->GetDeviceFileHandle( ), this->WriteBufferOnly, _BufferSize );
            }
        }
        catch( exception& e ) {
            snprintf( this->ErrMessage, sizeof( this->ErrMessage ), "Fatal I2C Error - Unable to write to file : %s", this->GetFilePath( ) );
            throw I2CSetupException( this->ErrMessage );
        }

        return EXIT_SUCCESS;
    }

}