#!/bin/bash

output="out.txt"

> $output

total_temp=0
total_count=0

for input_file in measurements*.txt; do
    if [[ -f $input_file ]]; then
        echo "File: $input_file" >> $output
        echo "TEMPERATURE TIME" >> $output
        sum_temp=0
        count=0
        temp=0
	time=0
	while IFS= read -r line
        do
            if [[ $line == Temperature:* ]]; then
                temp=$(echo $line | awk -F '[: ]+' '{print $2}')
                time=$(echo $line | awk -F '[: ]+' '{print $6}')
                echo "$temp $time" >> $output
                sum_temp=$(echo "$sum_temp + $temp" | bc)
                count=$((count + 1))
            fi
        done < "$input_file"
        total_temp=$(echo "$total_temp + $sum_temp" | bc)
        total_count=$((total_count + count))

        echo "end of $input_file" >> $output
    fi
done
if [[ $total_count -ne 0 ]]; then
	avg_temp=$(echo "scale=2; $total_temp / $total_count" | bc)
	echo "Overall Average Temperature: $avg_temp" >> $output
fi
