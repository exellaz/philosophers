#!/bin/bash

# Read the number of philosophers from user input
read -p "Enter the number of philosophers: " num_philosophers

# Simulate the output from a command
output=$(cat ./out)

# Initialize the counters
declare -a eating_counters
for ((i=0; i<num_philosophers; i++)); do
    eating_counters[$i]=0
done

# Loop through the output
while read line; do
    for ((i=1; i<=num_philosophers; i++)); do
        if [[ "$line" == *"$i is eating"* ]]; then
            ((eating_counters[$i-1]++))
        fi
    done
done <<< "$output"

# Calculate the total eating count
total_eating=0
for ((i=0; i<num_philosophers; i++)); do
    total_eating=$(($total_eating + ${eating_counters[$i]}))
done

# Total philo had eat
echo "Total philo eat: $total_eating"

# Print each philosopher's eating count
for ((i=0; i<num_philosophers; i++)); do
    if [ ${eating_counters[$i]} -ne 0 ]; then
        echo "philo $((i+1)) eat: ${eating_counters[$i]}"
    fi
done
