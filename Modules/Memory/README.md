# Memory Module
This module handles memory allocations. 
It is reccomended that all memory allocations route through this library (though not required.)

However, any PUBLIC memory allocations that it is up to the user to free, MUST be done through this library, as TP_MemFree should be used to free that data.