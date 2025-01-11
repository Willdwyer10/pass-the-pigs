#!/bin/bash

# Run the Python script with the specified input files and output file
python3 parser.py -d data.txt -c config.txt

# Display the contents of the output file
cat readable_output.txt
