#!/bin/bash

if [ $# -eq 0 ]; then
  echo "Usage: $0 number1 [number2 ... numberN]"
  exit 1
fi

for n in "$@"; do
    if ! [[ "$n" =~ ^[0-9]+$ ]]; then
    echo "$n is not a valid number."
    continue
  fi

  start_time=$(date +%s%N)

  factors=$(factor $n)
 
  end_time=$(date +%s%N)

  elapsed_time=$(( (end_time - start_time) / 1000000 ))

  factor_count=$(echo $factors | wc -w)
  if [ $factor_count -eq 2 ]; then
    echo "$n is a prime number. (Time taken: ${elapsed_time} ms)"
  else
    echo "$n is not a prime number. (Time taken: ${elapsed_time} ms)"
  fi
done
