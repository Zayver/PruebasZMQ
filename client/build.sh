#!/bin/bash
cd client
cmake CMakeLists.txt -B build
make -C build
cd ..
#./client/bin/client
