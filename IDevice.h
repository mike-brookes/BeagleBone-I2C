//
// Created by Michael Brookes on 09/04/2016.
//

#ifndef IDEVICE_H
#define IDEVICE_H

namespace IDevice {

    class IDevice {

        public:
            virtual ~IDevice( ) = 0;

        private:
            virtual int OpenDevice( ) = 0;
            virtual int WriteToDevice( int _BufferSize ) = 0;
            virtual short ReadDevice( int _BufferSize ) = 0;
            virtual int ConnectToDevice( ) = 0;

        protected:

    };

}
#endif //IDEVICE_H