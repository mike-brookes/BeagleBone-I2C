//
//  test.cpp
//  BBBAnalogDevice
//
//  Created by Michael Brookes on 04/10/2015.
//  Copyright © 2015 Michael Brookes. All rights reserved.
//

//#include "BBBI2CDevice.h"
#include "I2CDevice.h"

int main ( void ) {

    using namespace I2C;

    I2CDevice Accelerometer( 0x19, 1 );

    Accelerometer.SetRegisterValue( 0x77 ); //writing 0x77 to
    Accelerometer.SetRegisterAddress( 0x20 ); //register 0x20 activates the Accelerometer.

    Accelerometer.WriteToDevice( TWO_BYTES );

    short X = ( ( Accelerometer.GetValueFromRegister( 0x29 ) << 8 ) | Accelerometer.GetValueFromRegister( 0x28 ) );

    cout << "2. Print Value X : " << X << endl;

}