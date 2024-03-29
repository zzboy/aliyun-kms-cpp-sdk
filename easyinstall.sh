#!/bin/bash

MAKE=make
if command -v python > /dev/null ; then
  MAKE="make -j $(python -c 'import multiprocessing as mp; print(int(mp.cpu_count()))')"
fi

echo $MAKE

rm -rf sdk_build
mkdir sdk_build
cd sdk_build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local/ ..
$MAKE

make install
