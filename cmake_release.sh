#!/usr/bin/env bash

cd cmakebuild
cmake ../
cmake --build .
mv HelloWorld2 ../HelloWorld2
