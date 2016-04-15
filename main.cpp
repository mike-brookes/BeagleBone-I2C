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

    I2C->

  //  BBBI2CDevice QBBBI( 0x19, QBBBI.I2C1 );
  //  cout << "0x28 = " << QBBBI.I2C_GetValue( 0x28 );
  //  cout << " | 0x29 = " << QBBBI.I2C_GetValue( 0x29 ) << endl;

  //  QBBBI.I2C_WriteToReg( 0x20, 0x77 );

  //  cout << "0x28 = " << QBBBI.I2C_GetValue( 0x28 );
  //  cout << " | 0x29 = " << QBBBI.I2C_GetValue( 0x29 ) << endl;
}