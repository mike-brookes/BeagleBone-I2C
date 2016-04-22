# BeagleBoneBlack-I2C
Class for handling I2C devices on the BeagleBone Black

ReadMe
-------------

**This class is intended to be extended by classes for specific I2C devices (e.g LSM303DLHC)**

Designed specifically to run on the BeagleBone Black and provide an class that can easily be extended.

This project is a sub project of Quadro - Quadro contains the compiled binary for this class.

**Requirements**
- Beagle Bone Black [Purchase Info](https://www.adafruit.com/products/1996)
- An I2C Device *recommended* [10DOF IMU BreakOut](https://www.adafruit.com/products/1604)
  - Has onboard : L3GD20H + LSM303 + BMP180 (Accelerometer, Magnetometer, Gyro and Barometer)
- For testing purposes perhaps a [BreadBoard](https://www.adafruit.com/products/702) and [Jumper cables](https://www.adafruit.com/products/826)

**Setup**
- I used the default Debian install - Ubuntu will work just as well.
- JetBrains CLion IDE
- On a Mac book pro I use a SSHFS connection to automatically publish compiled binaries to the BBB *just to save time*
- xtools cross compiler for compiling compatible executables for the BBB.

**Notes**
By default I2C2 is available for use - this I2C Bus is available on Block P9 pins 19 (SCL) and 20 (SDA) see image below.
The header file can very easily be modified for other I2C Buses as required, just add a new constant I2C_# with the relevant file path and increment the total I2C Buses constant.

**Issues**
Please let me know of any problems and I will endeavour to assist!

![alt text](http://flyingbeaglebone.eu/images/BBblack_lg.jpg "I2C Pin Location")
