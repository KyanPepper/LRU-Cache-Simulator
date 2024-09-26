#include <stdio.h>
/// @brief This file is for IO operations for the cache simulation

typedef enum
{
    INSTRUCTION_LOAD, // 'I' - Instruction load
    DATA_LOAD,        // 'L' - Data load
    DATA_STORE,       // 'S' - Data store
    DATA_MODIFY,      // 'M' - Data modify (load followed by store)
    NONE              // - Used to indicate end of file or last operation
} MemOperation;

typedef struct
{
    MemOperation operation; // Type of memory operation
    int address;            // Memory address
    int size;               // Size of memory operation
} MemoryAccess;

typedef struct
{
    int opt;
    int s;
    int E;
    int b;
    char tracefile[64];
    int verbose;
    int err;
} CLOptions;

// Return command line arguments used in cache simulator
extern CLOptions getCommandLineArgs(int argc, char *argv[]);

// From a file create an operation to be preformed in cache simulator
extern MemoryAccess getAccess(FILE *tracefile);

/*
 * this function provides a standard way for your cache
 * simulator to display its final statistics (i.e., hit and miss)
 */
extern void print_summary(int hits, int misses, int evictions);

// for debugging purposes print the memory access operation
extern void print_memAccess(MemoryAccess operation);

// for debugging purposes print the command line arguments
extern void print_CLOptions(CLOptions options);
