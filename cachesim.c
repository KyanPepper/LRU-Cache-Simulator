#include "cachesim.h"

Cache createCache(int s, int E, int b)
{
    Cache cache;
    cache.indexBits = s;
    cache.lineCount = E;
    cache.offsetBits = b;
    cache.setsLen = (int)pow(2, s);
    cache.sets = (CacheSet *)malloc(sizeof(CacheSet) * cache.setsLen); // Allocate memory for each set

    for (int i = 0; i < cache.setsLen; i++)
    {
        cache.sets[i].lines = (CacheLine *)malloc(sizeof(CacheLine) * cache.lineCount); // Allocate memory for each line in the set
        for (int j = 0; j < cache.lineCount; j++)
        {
            cache.sets[i].lines[j].valid = 0;
            cache.sets[i].lines[j].tag = 0;
            cache.sets[i].lines[j].time = 0;
        }
    }
    return cache;
}

CacheStats initCacheStats()
{
    CacheStats stats;
    stats.hits = 0;
    stats.misses = 0;
    stats.evictions = 0;
    return stats;
}

// Reads or writes (same for the simulation) from the cache returns 1 if hit, 0 if miss, -1 for eviction
int read_write(Cache *cache, MemoryAccess memAccess)
{
    int setIndex = (memAccess.address >> cache->offsetBits) & ((1 << cache->indexBits) - 1); // Human readable: lhs (Shave off offset bits) & rhs (Mask index bits)
    int tag = memAccess.address >> (cache->indexBits + cache->offsetBits);                   // Human readable: lhs (Shave off offset and index bits by shifting over right)

    // Checks if hit and updates the cache line with the new memory access
    for (int i = 0; i < cache->lineCount; i++)
    {

        if (cache->sets[setIndex].lines[i].valid == 1 && cache->sets[setIndex].lines[i].tag == tag) // If valid and tag matches
        {

            cache->sets[setIndex].lines[i].time = clock(); // Update time
            return 1;                                      // Return Hit Value
        }
    }

    // Checks if cold miss and updates the cache line with the new memory access
    for (int i = 0; i < cache->lineCount; i++)
    {
        if (cache->sets[setIndex].lines[i].valid == 0)
        {
            cache->sets[setIndex].lines[i].valid = 1;
            cache->sets[setIndex].lines[i].tag = tag;
            cache->sets[setIndex].lines[i].time = clock();
            return 0; // Return Miss Value
        }
    }

    // Evicts a line from the cache
    int index = -1;            // Keep track of the line to evict
    time_t min = __LONG_MAX__; // Keep track of the smallest time value
    for (int i = 0; i < cache->lineCount; i++)
    {
        if (cache->sets[setIndex].lines[i].time < min)
        {
            index = i;
            min = cache->sets[setIndex].lines[i].time;
        }
    }

    cache->sets[setIndex].lines[index].tag = tag;
    cache->sets[setIndex].lines[index].time = clock();
    return -1; // Return Eviction Value
}

// Preforms calls to correct operation and updates the cache stats with results from the memory access
void preformAccess(Cache *cache, MemoryAccess memAccess, CacheStats *stats, CLOptions options)
{
    char str[64]; // String to hold the result of the memory access

    if (memAccess.operation == DATA_LOAD || memAccess.operation == DATA_STORE || memAccess.operation == DATA_MODIFY)
    {

        int result = read_write(cache, memAccess);
        switch (result)
        {
        case 1:
            strcpy(str, "hit");
            stats->hits++;
            break;
        case 0:
            strcpy(str, "miss");
            stats->misses++;
            break;
        case -1:
            strcpy(str, "miss");
            stats->evictions++;
            stats->misses++;
            break;
        default:
            break;
        }
    }

    if (memAccess.operation == DATA_MODIFY)
    {
        int result = read_write(cache, memAccess);
        switch (result)
        {
        case 1:
            strcat(str, " hit");
            stats->hits++;
            break;
        case 0:
            strcat(str, " miss");
            stats->misses++;
            break;
        case -1:
            strcat(str, " miss");
            stats->evictions++;
            stats->misses++;
            break;
        default:
            break;
        }
    }

    // Print the memory access if verbose is enabled
    if (options.verbose == 1)
    {
        print_memAccess(memAccess);
        printf(" %s\n", str);
    }
}
