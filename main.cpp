//
//  test.cpp
//  BBBAnalogDevice
//
//  Created by Michael Brookes on 04/10/2015.
//  Copyright © 2015 Michael Brookes. All rights reserved.
//

//#include "BBBI2CDevice.h"
#include "I2CDevice.h";

int main ( void ) {

    using namespace I2CDevice;

    I2CDevice I2C( 0x19, 1 );

    I2C.GetValueFromRegister( 0x28 );

    I2C.SetRegisterValue( 0x77 ); //writing 0x77 to
    I2C.SetRegisterAddress( 0x20 ); //register 0x20 activates the Accelerometer.

    I2C.WriteToDevice( TWO_BYTES );

}