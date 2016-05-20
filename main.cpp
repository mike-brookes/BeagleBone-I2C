//
//  test.cpp
//  BBBAnalogDevice
//
//  Created by Michael Brookes on 04/10/2015.
//  Copyright © 2015 Michael Brookes. All rights reserved.
//

#include "Lib/I2C/I2CDevice.h"

/*
 * Simplest implementation of a usable class extending an I2C device
 */
class LSM303DLHC : public abI2C::I2CDevice {
public:
    LSM303DLHC( ) { }
    void SetDeviceAddress( unsigned char _DeviceAddress ){ this->DeviceAddress = _DeviceAddress; }
    void SetBusId( int _BusId ) { this->BusId = _BusId; }
};

class LSM303_Accelerometer : public LSM303DLHC{
public:
    LSM303_Accelerometer( unsigned char _DeviceAddress, int _BusId ) {
        this->SetDeviceAddress( _DeviceAddress );
        this->SetBusId( _BusId );
        this->InitDevice( );
    }
};
/*
 * Test I2C functionality
 * Prints a short (8 bits) with current X reading from the accelerometer.
 */
int main ( void ) {

    using namespace abI2C;

    LSM303_Accelerometer *Accelerometer;

    Accelerometer = new LSM303_Accelerometer( 0x19, 1 );

    Accelerometer->SetRegisterValue( 0x77 ); //writing 0x77 to
    Accelerometer->SetRegisterAddress( 0x20 ); //register 0x20 activates the Accelerometer.

    Accelerometer->WriteToDevice( 2 );

    short X = ( ( Accelerometer->GetValueFromRegister( 0x29 ) << 8 ) | Accelerometer->GetValueFromRegister( 0x28 ) );

    cout << "2. Print Value X : " << X << endl;

}