#!/bin/bash
cd load_balancer
cmake CMakeLists.txt -B build
make -C build
cd ..
#./load_balancer/bin/load_balancer

