//
// Created by Michael Brookes on 19/04/2016.
//

#ifndef BBBI2CDEVICE_EXCEPTIONAID_H
#define BBBI2CDEVICE_EXCEPTIONAID_H

#include <exception>
#include <iostream>

namespace I2CDevice {
    using namespace std;

    class I2CSetupException : public exception {
    public:
        I2CSetupException(const char* errMessage):errMessage_(errMessage){}
        const char* what() const throw() { return errMessage_; }

    private:
        const char* errMessage_;
    };

}

#endif //BBBI2CDEVICE_EXCEPTIONAID_H
