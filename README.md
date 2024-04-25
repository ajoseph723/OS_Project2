# OS_Project2
# Banker's Algorithm in C++

## Overview
This C++ program implements the Banker's algorithm for deadlock avoidance. It reads a system snapshot from an input file (`bankers_input.txt`), calculates the need matrix, and determines if the system is in a safe state. If the system is in a safe state, it prints out the safe sequence of processes.

## Compilation and Execution
1. Compile the program using the following command:
    g++ -o bankers algorithm.cpp

2. Run the compiled executable:
    ./bankers

3. The program will read the system snapshot from `bankers_input.txt`, perform the Banker's algorithm, and print out whether the system is in a safe state or not, along with the safe sequence of processes.

## Input File Format
The input file `bankers_input.txt` should have the following format:
<Number of processes> <Number of resources>
<Allocation matrix>
<Max matrix>
<Available resources>

## Output
- If the system is in a safe state, the program will print "System is in safe state." followed by the safe sequence of processes.
- If the system is not in a safe state, the program will print "System is not in safe state."