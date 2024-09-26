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
            cache.sets[i].lines[j].last_used = 0;
        }
    }
    return cache;
}
