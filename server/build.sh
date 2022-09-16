#!/bin/bash
cd server
cmake CMakeLists.txt -B build
make -C build
cd ..
#./server/bin/load_balancer
