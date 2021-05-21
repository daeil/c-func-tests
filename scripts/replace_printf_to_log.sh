#!/bin/bash

for file in $(find . -name "*.c")
do
    echo "process file: $file"
    sed -r -e '/\bprintf\b/{s/printf/logV/;s/(.*)\\n/\1/g}' $file
done

