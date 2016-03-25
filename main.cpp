//
//  test.cpp
//  BBBAnalogDevice
//
//  Created by Michael Brookes on 04/10/2015.
//  Copyright © 2015 Michael Brookes. All rights reserved.
//

#include "BBBI2CDevice.h"

using namespace std;

int main ( void ) {
    BBBI2CDevice QBBBI( 0x19, QBBBI.I2C1 );
    cout << "0x28 = " << QBBBI.I2C_GetValue( 0x28 );
    cout << " | 0x29 = " << QBBBI.I2C_GetValue( 0x29 ) << endl;

    QBBBI.I2C_WriteToReg( 0x20, 0x77 );

    cout << "0x28 = " << QBBBI.I2C_GetValue( 0x28 );
    cout << " | 0x29 = " << QBBBI.I2C_GetValue( 0x29 ) << endl;
}