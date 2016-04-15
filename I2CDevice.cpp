//
// Created by Michael Brookes on 14/04/2016.
//

#include "I2CDevice.h"

namespace I2CDevice {

    I2CDevice::I2CDevice( int _DeviceAddress, int _BusId ) {

        /*
         * Setup Stage
         */
        this->SetBusPaths( );

        /*
         * Assignment Stage ( based on args )
         */
        this->SelectABusPath( _BusId );
        this->SetDeviceAddress( _DeviceAddress );

        /*
         * Init Stage
         */
        this->OpenDevice( );
        this->ConnectToDevice( );

    }

    I2CDevice::~I2CDevice( ) { }

    void I2CDevice::SetBusPaths( ) {
        this->_Bus[ 1 ].BusPath = I2C_1;
        this->_Bus[ 2 ].BusPath = I2C_2;
    }

    void I2CDevice::SelectABusPath( int _BusId ) { this->DeviceBusPath = this->_Bus[ _BusId ].BusPath; }

    void I2CDevice::SetRegisterValue( unsigned char _RegisterValue ){ this->RegisterValue = _RegisterValue; }

    void I2CDevice::SetRegisterAddress( unsigned char _RegisterAddress ){ this->RegisterAddress = _RegisterAddress; }

    void I2CDevice::SetDeviceAddress( int _DeviceAddress ) { this->DeviceAddress = _DeviceAddress; }

    const char * I2CDevice::GetFilePath( ) { return this->DeviceBusPath; }

    int I2CDevice::GetDeviceFileHandle( ) { return this->FileHandle; }

    short I2CDevice::GetValueFromRegister( unsigned char _RegisterValue ) {
        this->SetRegisterValue( _RegisterValue );
        if( this->WriteToDevice( READ_LEN ) == READ_LEN )
            this->ReadDevice( READ_LEN );
        else
            return -1;
    }

    short I2CDevice::ReadDevice( int _BufferSize ) {
        unsigned char buff[ _BufferSize ];
        try {
            if( read( this->GetDeviceFileHandle( ), buff, _BufferSize ) != _BufferSize )
                return -1;
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

    /*!
    \fn private function WriteToReg( int RegToWriteTo, int ValToWriteToReg )
    \brief Writes to the RegToWriteTo value.
    \param <int> RegToWriteTo (hex format), <int> ValToWriteToReg (hex format)
    \return <int> -1 = failure to open the bus, 0 = success
    */
    int I2CDevice::WriteToDevice( size_t _BufferSize  ) {
        if( _BufferSize > READ_LEN ) {
            this->ReadAndWriteBuffer[ 0 ] = this->RegisterAddress;
            this->ReadAndWriteBuffer[ 1 ] = this->RegisterValue;
        }
        else
            this->WriteBufferOnly[ 0 ] = this->RegisterValue;

        try {
            if( write( this->GetDeviceFileHandle( ), this->ReadAndWriteBuffer, _BufferSize ) != _BufferSize )
                return -1;
            else
                return 0;
        }
        catch( exception& e ) {
            cerr << "Fatal Exception Raised : Writing " << e.what( ) << endl;
            exit( EXIT_FAILURE );
        }
    }


}