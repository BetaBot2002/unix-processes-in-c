#!/bin/bash

# Check if the source file is provided as an argument
if [ -z "$1" ]; then
  echo "Usage: $0 <./path/filename>.c"
  exit 1
fi

# Get the filename without the extension
filename=$(basename "$1" .c)

# Create the outputs directory only if it doesn't exist
if [ ! -d "./outputs" ]; then
  echo "Creating outputs directory..."
  mkdir -p ./outputs
  echo "Outputs directory created."
fi

# Start the timer (in milliseconds)
start_time=$(date +%s%3N)

# Compile the C file
echo "Compiling $1..."
gcc "$1" -o "./outputs/$filename"

# Check if the compilation was successful
if [ $? -eq 0 ]; then
  echo "Compilation successful."

  # Run the compiled program
  echo "Running the program..."
  echo "-------------------------------"
  ./outputs/$filename
  echo "-------------------------------"
  echo "Program execution completed."
else
  echo "Compilation failed."
  exit 1
fi

# End the timer (in milliseconds)
end_time=$(date +%s%3N)

# Calculate the time taken in milliseconds
time_taken=$((end_time - start_time))

# Print the time taken
echo "Time taken: $time_taken milliseconds."
