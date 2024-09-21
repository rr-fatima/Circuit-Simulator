#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

// Function prototypes
void handleInsert(LinkedList*);
void handleRemove(LinkedList*);
void handleCurrentCal(LinkedList*, int);
void handleVoltage(LinkedList*, int);
void handlePrint(LinkedList*);
void handleQuit(LinkedList*);

int main(void) {
  LinkedList circuit;
  initList(&circuit);  // Initialize the linked list for the circuit
  char command = '\0';  // Variable to store user command
  printf("Welcome to our circuit simulator\n");
  
  // Prompt user for the source voltage
  printf("What is the source of the voltage?\n");
  int voltage;
  readInputNumber(&voltage);  // Read the source voltage from user

  // Main loop to process user commands
  while (command != 'Q') {
    command = getCommand();  // Get command from user

    // Execute the appropriate command
    switch (command) {
      case 'I':
        handleInsert(&circuit);  // Insert a new resistor
        break;
      case 'R':
        handleRemove(&circuit);  // Remove a resistor
        break;
      case 'C':
        handleCurrentCal(&circuit, voltage);  // Calculate current
        break;
      case 'V':
        handleVoltage(&circuit, voltage);  // Calculate voltage across a resistor
        break;
      case 'P':
        handlePrint(&circuit);  // Print all resistors
        break;
      case 'Q':
        handleQuit(&circuit);  // Quit and clean up
        break;
    }
  }
  return 0;
}

void handleInsert(LinkedList* circuit) {
  int resistance = 0;
  // Prompt user for resistor value
  printf("What's the value of the resistor: ");
  readInputNumber(&resistance);
  
  // Prompt user for resistor label
  printf("What's the label of the resistor: ");
  char labelName[STRING_MAX];
  readInputString(labelName, STRING_MAX);
  
  // Create a new node for the resistor
  Node* newNode = (Node*) malloc(sizeof(Node)); 
  newNode->value = resistance;
  strcpy(newNode->name, labelName);
  newNode->next = NULL;

  // If the list is empty, insert the new node as the head
  if (!circuit->head) {
    circuit->head = newNode;
    return;
  }
  
  // Insert the new node in alphabetical order
  Node* tempNode = circuit->head;
  if(strcmp(tempNode->name, newNode->name) > 0) { // New node becomes the head
    circuit->head = newNode;
    newNode->next = tempNode;
    return;
  }
   
  // Traverse the list to find the correct insertion point
  while(tempNode) {
    if (strcmp(tempNode->name, newNode->name) == 0) {
      printf("A resistor with %s label already exists.\n", tempNode->name);
      free(newNode);  // Free memory if label exists
      return;
    }

    if (!tempNode->next) {  // If reached the end, insert new node
      tempNode->next = newNode;
      return;
    }

    if (strcmp(tempNode->next->name, newNode->name) > 0) {  // Insert in order
      newNode->next = tempNode->next;
      tempNode->next = newNode;
      return;
    }
    tempNode = tempNode->next;  // Move to next node
  }
}

void handleRemove(LinkedList* circuit) {
  // Prompt user for the label of the resistor to remove
  printf("What's the label of the resistor you want to remove: ");
  char labelName[STRING_MAX];
  readInputString(labelName, STRING_MAX);

  Node* tempNode = circuit->head;
  // If the resistor to be deleted is the head
  if (strcmp(tempNode->name, labelName) == 0) {
    circuit->head = tempNode->next;  // Update head
    free(tempNode);  // Free memory
    return;
  }

  Node* prevNode = tempNode;  // Keep track of the previous node
  tempNode = tempNode->next;  // Move to the next node
  while (tempNode) {
    if (strcmp(tempNode->name, labelName) == 0) {
      prevNode->next = tempNode->next;  // Bypass the node to be deleted
      free(tempNode);  // Free memory
      return;
    }
    prevNode = tempNode;  // Move to next node
    tempNode = tempNode->next;
  }

  // If resistor was not found
  printf("The resistor with %s label does not exist.\n", labelName);
}

void handleCurrentCal(LinkedList* circuit, int voltage) {
  int totalRes = 0;
  
  Node* tempNode = circuit->head;
  // Sum up the resistances in the circuit
  while (tempNode) {
    totalRes += tempNode->value; 
    tempNode = tempNode->next;
  }

  // Calculate and display the current
  printf("The current in the circuit is %.6fA\n", (double) voltage / totalRes);
}

void handleVoltage(LinkedList* circuit, int voltage) {
  // Prompt user for the label of the resistor to find voltage across
  printf("What's the label of the resistor you want to find the voltage across: ");
  char labelName[STRING_MAX];
  readInputString(labelName, STRING_MAX);

  int totalRes = 0;
  double current;
  int resistorVal = -1;  // Default to -1 to indicate not found
  
  Node* tempNode = circuit->head;
  // Calculate total resistance and find the specific resistor
  while (tempNode) {
    totalRes += tempNode->value;
    if (strcmp(tempNode->name, labelName) == 0) {
      resistorVal = tempNode->value;  // Store resistor value
    }
    tempNode = tempNode->next;
  }

  // Check if the resistor was found
  if (resistorVal == -1) {
    printf("The resistor with %s label does not exist.\n", labelName);
    return;
  }

  // Calculate the current and voltage across the specified resistor
  current = (double) voltage / totalRes;
  printf("Voltage across resistor is %.6fV\n", current * resistorVal);
}

void handlePrint(LinkedList* circuit) {
  Node* tempNode = circuit->head;
  // Print all resistors in the circuit
  while (tempNode) {
    printf("%s\t%d Ohms\n", tempNode->name, tempNode->value);
    tempNode = tempNode->next;
  }
}

void handleQuit(LinkedList* circuit) {
  Node* tempNode = circuit->head;
  Node* delNode;
  printf("Removing all resistors in the circuit ...\n");
  
  // Free all nodes in the list
  while (tempNode) {
    printf("%s\t%d Ohms\n", tempNode->name, tempNode->value);
    delNode = tempNode;  // Keep track of the node to delete
    tempNode = tempNode->next;  // Move to the next node
    free(delNode);  // Free memory
  }
}
