#!/bin/bash

function build_test() {
    mkdir build
    cd build
    cmake ../
    cmake --build . && ctest .
}

if [ $# = 0 ]; then
    docker run --rm -v ${PWD}:/code -it srzzumix/googletest ./build.sh 1
    exit 1
fi

build_test
