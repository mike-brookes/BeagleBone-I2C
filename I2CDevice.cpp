//
// Created by Michael Brookes on 14/04/2016.
//

#include "I2CDevice.h"

namespace I2CDevice {

    I2CDevice::I2CDevice( int _DeviceAddress, int _BusId ) {

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
        this->_Bus[ 1 ].BusPath = I2C_1;
        this->_Bus[ 2 ].BusPath = I2C_2;
    }

    void I2CDevice::SelectABusPath( I2CBus _I2CBus ) { this->DeviceBusPath = _I2CBus.BusPath; }

    void I2CDevice::SetRegisterValue( unsigned char _RegisterValue ){ this->RegisterValue = _RegisterValue; }

    void I2CDevice::SetRegisterAddress( unsigned char _RegisterAddress ){ this->RegisterAddress = _RegisterAddress; }

    void I2CDevice::SetDeviceAddress( int _DeviceAddress ) { this->DeviceAddress = _DeviceAddress; }

    const char * I2CDevice::GetFilePath( ) { return this->DeviceBusPath; }

    int I2CDevice::GetDeviceFileHandle( ) { return this->FileHandle; }

    int I2CDevice::ValidateBusId( int _BusId ) {
        this->BusId = _BusId;
        if( this->BusId > I2C_BUS_COUNT || this->BusId < 1 ) {
            cerr <<  "Bus ID : " << _BusId << " is not a valid BUS for this device." << endl;
            return EXIT_FAILURE;
        }
        else
            return EXIT_SUCCESS;
    }

    short I2CDevice::GetValueFromRegister( unsigned char _RegisterValue ) {
        this->SetRegisterAddress( _RegisterValue );
        if( this->WriteToDevice( ONE_BYTE ) == ONE_BYTE )
            return this->ReadDevice( ONE_BYTE );
        else
            return EXIT_FAILURE;
    }

    short I2CDevice::ReadDevice( size_t _BufferSize ) {
        unsigned char buff[ _BufferSize ];
        try {
            if( read( this->GetDeviceFileHandle( ), buff, _BufferSize ) != _BufferSize )
                return EXIT_FAILURE;
            else
                return buff[ 0 ];
        }
        catch( exception& e ) {
            cerr << "Fatal Exception Raised : Reading " << e.what( ) << endl;
            exit( EXIT_FAILURE );
        }
    }

    int I2CDevice::OpenDevice( ) {
        try {
            this->FileHandle = open( this->GetFilePath( ), O_RDWR );
        }
        catch( exception& e ){
            cerr << "Fatal Exception Raised : Opening " << this->GetFilePath( ) << " for RDWR. Error : " << e.what( ) << endl;
            exit( EXIT_FAILURE );
        }
        return this->FileHandle;
    }

    int I2CDevice::WriteToDevice( size_t _BufferSize  ) {
        int res;
        try {
            if( _BufferSize > ONE_BYTE ) {
                this->ReadAndWriteBuffer[ 0 ] = this->RegisterAddress;
                this->ReadAndWriteBuffer[ 1 ] = this->RegisterValue;
                res = write( this->GetDeviceFileHandle( ), this->ReadAndWriteBuffer, _BufferSize );
            }
            else {
                this->WriteBufferOnly[ 0 ] = this->RegisterValue;
                res = write( this->GetDeviceFileHandle( ), this->ReadAndWriteBuffer, _BufferSize );
            }
        }
        catch( exception& e ) {
            cerr << "Fatal Exception Raised : Writing " << e.what( ) << endl;
            exit( EXIT_FAILURE );
        }
        if( res != _BufferSize )
            return EXIT_FAILURE;
        else
            return EXIT_SUCCESS;
    }

}