#!/bin/bash

INPUT_FILE=$1

cat "$INPUT_FILE" | python mapper.py | sort | python reducer.py
