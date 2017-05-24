#!/bin/bash
# Build and run the instrumented executable

AFL=~/Nextcloud/src/afl/afl-2.41b
export CC=$AFL/afl-clang
export CXX=$AFL/afl-clang++

set -x

mkdir -p aflbuild \
&& cd aflbuild \
&& cmake .. \
&& make \
&& $AFL/afl-fuzz -i ../testcases -o ../findings ./afldemo
