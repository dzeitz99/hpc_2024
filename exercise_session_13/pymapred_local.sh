#!/bin/bash

if [ "$#" -ne 1 ]; then
	echo "Input is: $0 <input_file>"
	exit 1
fi

INPUT_FILE=$1

cat "$INPUT_FILE" | python mapper.py | sort | python reducer.py
