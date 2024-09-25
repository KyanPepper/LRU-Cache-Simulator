#include <stdio.h>
//Structures
typedef enum {
    INSTRUCTION_LOAD,  // 'I' - Instruction load 
    DATA_LOAD,         // 'L' - Data load
    DATA_STORE,        // 'S' - Data store
    DATA_MODIFY        // 'M' - Data modify (load followed by store)
} MemOperation;

typedef struct {
    MemOperation operation; // Type of memory operation
    int address; // Memory address
    int size; // Size of memory operation
} MemoryAccess;

// From a file create an operation to be preformed in cache simulator
extern void populateOperations();

// For debugging purposes
extern void print_operation(MemoryAccess operation);