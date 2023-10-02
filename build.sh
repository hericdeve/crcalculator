#!/bin/bash

# Function to build the program
build_program() {
    # Create the build directory and change to it
    mkdir -p build && cd build

    # Run CMake and make
    cmake ..
    make
}

# Function to clean the build files
clean_build() {
    # Remove the build directory
    rm -rf build
}

# Check the command line arguments
if [ "$1" == "clean" ]; then
    clean_build
else
    build_program
fi
