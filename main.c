#include "cachesim.h"
#include "cacheio.h"
int main(int argc, char *argv[])
{
    CLOptions options = getCommandLineArgs(argc, argv);
    print_CLOptions(options);

    FILE *trace_file = fopen(options.tracefile, "r");

    if (options.err == 1)
    {
        printf("Error: Invalid command line options\n");
        return 1;
    }

    if (trace_file == NULL)
    {
        printf("Error: Could not open file %s\n", options.tracefile);
        return 1;
    }
    //Simulator runs in the main loop  
    while (1)
    {
        MemoryAccess memAccess = getAccess(trace_file);
        if (memAccess.operation == NONE)
        {
            break;
        }
    }
    fclose(trace_file);

    
    return 0;
}