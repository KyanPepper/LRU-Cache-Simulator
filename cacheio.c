#include "cacheio.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// Parse the operation character to a MemOperation
static MemOperation parse_operation(char op_char)
{
    switch (op_char)
    {
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
        return NONE;
    }
}

// Print the operation to the console
void print_memAccess(MemoryAccess operation)
{
    printf("Printing Operation: ");
    switch (operation.operation)
    {
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

/*
 * this function provides a standard way for your cache
 * simulator to display usage information
 */

static void print_usage(char *argv[])
{
    printf("Usage: %s [-hv] -s <num> -E <num> -b <num> -t <file>\n", argv[0]);
    printf("Options:\n");
    printf("  -h         Print this help message.\n");
    printf("  -v         Optional verbose flag.\n");
    printf("  -s <num>   Number of set index bits.\n");
    printf("  -E <num>   Number of lines per set.\n");
    printf("  -b <num>   Number of block offset bits.\n");
    printf("  -t <file>  Trace file.\n");
    printf("\nExamples:\n");
    printf("  linux>  %s -s 4 -E 1 -b 4 -t traces/trace01.dat\n", argv[0]);
    printf("  linux>  %s -v -s 8 -E 2 -b 4 -t traces/trace01.dat\n", argv[0]);
    exit(0);
}

void print_CLOptions(CLOptions options)
{
    printf("Printing Command Line Options:\n");
    printf("Verbose: %d\n", options.verbose);
    printf("s: %d\n", options.s);
    printf("E: %d\n", options.E);
    printf("b: %d\n", options.b);
    printf("Tracefile: %s\n", options.tracefile);
}

MemoryAccess getAccess(FILE *trace_file)
{
    MemoryAccess memAccess = {NONE, 0, 0};
    char op_char;
    int address;
    int size;
    if (fscanf(trace_file, " %c %x,%d", &op_char, &address, &size) != EOF)
    {
        memAccess.operation = parse_operation(op_char);
        memAccess.address = address;
        memAccess.size = size;
    }
    print_memAccess(memAccess);
    return memAccess;
}

CLOptions getCommandLineArgs(int argc, char *argv[])
{
    CLOptions options = {0, -1, -1, -1, "", 0, 0};
    int opt;
    while ((opt = getopt(argc, argv, "hvs:E:b:t:")) != -1)
    {
        switch (opt)
        {
        case 'h':
            print_usage(argv);
            break;
        case 'v':
            options.verbose = 1;
            break;
        case 's':
            options.s = atoi(optarg);
            break;
        case 'E':
            options.E = atoi(optarg);
            break;
        case 'b':
            options.b = atoi(optarg);
            break;
        case 't':
            strcpy(options.tracefile, optarg);
            break;
        default:
            options.err = 1;
            break;
        }
    }
    return options;
}
