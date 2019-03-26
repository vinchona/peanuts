#!/bin/bash

./scripts/reformat.sh

./bin/tester.exe
echo $?

./bin/fuzzer.exe --size 256
echo $?

