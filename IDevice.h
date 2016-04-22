//
// Created by Michael Brookes on 09/04/2016.
//

#ifndef IDEVICE_H
#define IDEVICE_H

#include <cstdio>

namespace IDevice {

    class IDevice {

        public:
            virtual ~IDevice( ){ };

        private:
            virtual int OpenDevice( ) = 0;
            virtual int WriteToDevice( size_t _BufferSize ) = 0;
            virtual short ReadDevice( size_t _BufferSize ) = 0;
            virtual int ConnectToDevice( ) = 0;

        protected:

    };

}
#endif //IDEVICE_H