#!/bin/zsh
cd $(cd `dirname $0`/..; pwd)
cmake -B build/xcode -G Xcode
cmake --open build/xcode