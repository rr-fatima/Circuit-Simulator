# Circuit-Simulator

This text-based circuit simulator models a series circuit of resistors using a linked list in C. Each resistor is represented as a node in the list, containing its resistance value (in Ohms) and a label. The program allows users to manage a circuit by adding and removing resistors, calculating the current flowing through the circuit, and determining the voltage across individual resistors. The linked list maintains an alphabetical order of resistors based on their labels, ensuring efficient management and retrieval.

The program is implemented using the C standard libraries, including `math.h`, `stdbool.h`, `stdio.h`, `stdlib.h`, and a custom `linkedlist.h` for linked list operations.

# How the Program Works

1. **Initialization**  
   - The program starts by initializing a linked list to store resistors and prompts the user for the source voltage (in volts) for the circuit.
   - A menu-driven interface presents five commands to the user:  
     - **I**: Insert a new resistor  
     - **R**: Remove a resistor  
     - **C**: Calculate the current through the circuit  
     - **P**: Print the labels and values of all resistors  
     - **V**: Calculate the voltage across a specific resistor  
     - **Q**: Quit the program and free all allocated memory

2. **User Interaction**  
   - The user can enter a command to perform the desired action. For example:  
     - When inserting a resistor, the program prompts for the resistor's value and label, creating a new node with `malloc` and inserting it in the correct alphabetical position.  
     - For removal, the user provides the label of the resistor, and the program searches for it in the list to delete the corresponding node and free its memory.

3. **Calculations**  
   - The program calculates the total resistance by traversing the linked list and computes the current using Ohm's law: I = V/R . It also allows for voltage calculations across individual resistors based on the current and resistance.

4. **Memory Management**  
   - The program manages memory efficiently by allocating memory for new nodes using `malloc` and freeing memory for deleted nodes with `free`. Upon quitting, all nodes are freed, and their labels are printed to confirm the deletion.

This simulator provides a simple yet effective way to understand the behavior of resistors in series circuits through a user-friendly interface.
