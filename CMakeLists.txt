cmake_minimum_required(VERSION 3.3)
project(BBBI2CDevice)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(CMAKE_SYSROOT /Volumes/xtools/arm-none-linux-gnueabi/arm-none-linux-gnueabi/sysroot/)

set(CMAKE_CXX_COMPILER /Volumes/xtools/arm-none-linux-gnueabi/bin/arm-none-linux-gnueabi-g++)

set(SOURCE_FILES main.cpp BBBI2CDevice.cpp BBBI2CDevice.h main.cpp)
add_library(BBBI2CDevice STATIC ${SOURCE_FILES} main.cpp)