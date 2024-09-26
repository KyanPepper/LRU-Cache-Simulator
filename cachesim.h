#include <getopt.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>
#define ADDRESS_LENGTH 64 // 64-bit memory addressing

typedef struct CacheLine
{
    int valid;
    int tag;
    int last_used;
} CacheLine;

typedef struct CacheSet
{
    struct CacheLine *lines;
} CacheSet;

typedef struct Cache
{
    int indexBits;
    int lineCount;
    int offsetBits;
    int setsLen; // Number of sets in the cache
    CacheSet *sets;
} Cache;

// Creates a cache with s sets, E lines per set, and b block bits
extern Cache createCache(int s, int E, int b);

extern void freeCache(Cache *cache);