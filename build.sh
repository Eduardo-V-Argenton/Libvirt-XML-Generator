#!/bin/bash

# Exit immediately if a command exits with a non-zero status
set -e

# Define your build directory
BUILD_DIR=build

# Create the build directory if it doesn't exist
if [ ! -d "$BUILD_DIR" ]; then
    mkdir "$BUILD_DIR"
fi

# Install dependencies with Conan
conan install . --output-folder=build --build=missing

# Change to the build directory
cd "$BUILD_DIR"

# Run CMake
cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release

# Build the project
cmake --build .

echo "Build completed successfully!"