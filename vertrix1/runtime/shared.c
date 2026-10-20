/* vertrix3's memory, x87 helpers and call dispatcher, compiled against this runtime's headers:
 * they are included first, and their guards keep vertrix3's own copies out. */
#include "runtime.h"
#include "threads.h"

#include "../../vertrix3/runtime/cpu.c"
#include "../../vertrix3/runtime/memory.c"
