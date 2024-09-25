#include <getopt.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>

#define ADDRESS_LENGTH 64  // 64-bit memory addressing

/* 
 * this function provides a standard way for your cache
 * simulator to display its final statistics (i.e., hit and miss)
 */ 
extern void print_summary(int hits, int misses, int evictions);


/* 
 * this function provides a standard way for your cache
 * simulator to display usage information
 */
extern void print_usage(char* argv[]);
