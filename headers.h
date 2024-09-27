// Assign correct type to operating system
#ifdef __APPLE__
#define int64 long long
#else
#define int64 long
#endif

// Define printf operation for address
#ifdef __APPLE__
#define F_ADDRESS "%llx"
#else
#define F_ADDRESS "%lx"
#endif
