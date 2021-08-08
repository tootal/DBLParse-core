#!/bin/zsh
cd $(cd `dirname $0`/..; pwd)

cmake -B build
cmake --build build