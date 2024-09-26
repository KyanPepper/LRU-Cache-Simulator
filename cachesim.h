#include <getopt.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <time.h>
#include <string.h>
#include "cacheio.h"

#define ADDRESS_LENGTH 64 // 64-bit memory addressing

typedef struct CacheLine
{
    int valid;
    int tag;
    time_t time; // Last time the line was used: Evict Smallest Value
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

typedef struct CacheStats
{
    int hits;
    int misses;
    int evictions;
} CacheStats;

// Creates a cache with s sets, E lines per set, and b block bits
extern Cache createCache(int s, int E, int b);

// Seeds stats with 0 hits, misses, and evictionss
extern CacheStats initCacheStats();

// Preforms calls to correct operation and updates the cache stats with results from the memory access
extern void preformAccess(Cache *cache, MemoryAccess memAccess, CacheStats *stats, CLOptions options);

//Prints the cache summary
extern void printCacheStats(CacheStats stats);

