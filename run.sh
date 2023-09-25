#!/bin/bash

# Check if at least one argument is provided
if [ "$#" -lt 1 ]; then
    echo "Usage: $0 <file_stem> [args...]"
    exit 1
fi

# Extract the file stem and append .cpp extension
FILESTEM=$1
FILENAME="$FILESTEM.cpp"
shift

# Create the out directory if it doesn't exist
mkdir -p out

# Compile the C++ file into the out directory
g++ $FILENAME -o out/$FILESTEM

# Check if compilation was successful
if [ $? -ne 0 ]; then
    echo "Compilation failed!"
    exit 1
fi

# Run the compiled program with the rest of the arguments
./out/$FILESTEM "$@"