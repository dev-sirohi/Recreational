#!/bin/sh

if [ -z "$1" ]; then
    echo "Usage: bash runner.sh <output_name>"
    exit 1
fi

mkdir -p executables
gcc -g \
    -Wall -Wextra \
    exception-handling.c \
    main.c \
    -o "executables/$1"

./executables/"$1"
