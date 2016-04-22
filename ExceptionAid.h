//
// Created by Michael Brookes on 19/04/2016.
//

#ifndef I2C_EXCEPTION_AID_H
#define I2C_EXCEPTION_AID_H

#include <exception>
#include <iostream>

namespace I2C {
    using namespace std;

    class I2CSetupException : public exception {
    public:
        I2CSetupException( char* errMessage ):errMessage_(errMessage){}
        const char* what() const throw() { return errMessage_; }

    private:
        char* errMessage_;
    };
}

#endif //I2C_EXCEPTION_AID_H
