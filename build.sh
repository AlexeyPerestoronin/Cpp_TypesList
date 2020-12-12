#!/bin/bash -e

BUILD_TYPE=${1}

if [ ${BUILD_TYPE} = "Release" ]; then
    echo "[INFO] build type is '${BUILD_TYPE}'"
elif [ ${BUILD_TYPE} = "Debug" ]; then
    echo "[INFO] build type is '${BUILD_TYPE}'"
else
    echo "[ERROR] usage: build.sh <Release|Debug>"
    exit 1;
fi

mkdir -p build
cd build

cmake .. -DCMAKE_BUILD_TYPE=${BUILD_TYPE}

cmake --build . --config ${BUILD_TYPE};
