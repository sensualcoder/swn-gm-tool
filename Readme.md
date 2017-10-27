# Stars Without Number GM Tool
A GM tool for the Stars Without Number game system. The purpose of this tool is to streamline the process of creating factions and running the GM turn portion of a SWN campaign.

## Prerequisites
- A C++11 compatible compiler ([ref](http://en.cppreference.com/w/cpp/compiler_support#cpp11))
- [cmake](https://cmake.org/)
- make

## Third-party libraries
- [Catch](https://github.com/philsquared/Catch) - Unit testing library
- [cereal](https://github.com/USCiLab/cereal) - Serialization library

## Build
- Create a build directory and change to the new directory.

`$ mkdir build`

`$ cd build`
- Run cmake to create the makefiles for the build

`$ cmake ..`

- Run make to build the tests and SwnGmTool binary

`$ make`
- Run the tests

`$ ./Tests/tests`

- Run the driver program to play with it.

`$ ./SwnGmTool`
