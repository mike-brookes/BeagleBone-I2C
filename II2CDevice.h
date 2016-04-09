//
// Created by Michael Brookes on 09/04/2016.
//

#ifndef II2CDEVICE_H
#define II2CDEVICE_H

#include "IDevice.h"

namespace II2CDevice {
    class II2CDevice : public IDevice {
    public:
        virtual ~II2CDevice( ) = 0;
    private:
        enum I2CBus { I2C1 = 1, I2C2 = 2, I2C3 = 3 };
    protected:
        virtual int setI2CBus( I2CBus _I2C_Bus ) = 0;
        virtual int setI2CBusAddress(  ) = 0;
        virtual int connect( ) = 0;
    };
}

#endif //II2CDEVICE_H
