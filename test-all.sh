#!/bin/bash

for i in test/*.in ; do
    echo "Test case: $i";
    ./out/bin/regexsf < $i 2>/dev/null
done