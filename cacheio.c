#include "cacheio.h"
#include <stdlib.h>


static MemOperation parse_operation(char op_char) {
    switch (op_char) {
        case 'I':
            return INSTRUCTION_LOAD; 
        case 'L':
            return DATA_LOAD;
        case 'S':
            return DATA_STORE;
        case 'M':
            return DATA_MODIFY;
        default:
            printf("Unknown operation: %c\n", op_char);
            return INSTRUCTION_LOAD;
    }
}


MemoryAccess getOperation(FILE *trace_file) {
    MemoryAccess operation = {INSTRUCTION_LOAD,0,0};
    char op_char;
    int address;
    int size;
    if (fscanf(trace_file, " %c %x,%d", &op_char, &address, &size)) {
        operation.operation = parse_operation(op_char);
        operation.address = address;
        operation.size = size;
    }
    print_operation(operation);
    return operation;
}

void print_operation(MemoryAccess operation) {
    switch (operation.operation) {
        case INSTRUCTION_LOAD:
            printf("I");
            break;
        case DATA_LOAD:
            printf("L");
            break;
        case DATA_STORE:
            printf("S");
            break;
        case DATA_MODIFY:
            printf("M");
            break;
        default:
            printf("Unknown operation");
    }
    printf(" %x,%d\n", operation.address, operation.size);
}