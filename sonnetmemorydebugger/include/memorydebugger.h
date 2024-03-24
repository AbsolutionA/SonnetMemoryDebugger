#ifndef S_MEMORY_DEBUGGER_H
#define S_MEMORY_DEBUGGER_H


// Debugging on memory management 

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
extern void *s_debug_memory_malloc(uint32_t size, char *file, uint32_t line);
extern void s_debug_memory_free(void *buffer, char *file, uint32_t line);
extern void s_debug_memory_info_print();


// Replace the memory management function with the debug versions
#ifdef S_DEBUG_MEMORY_ON

#define malloc(n) s_debug_memory_malloc(n, __FILE__, __LINE__)
#define free(n) s_debug_memory_free(n, __FILE__, __LINE__)

#endif // S_DEBUG_MEMORY_ON
#endif // S_MEMORY_DEBUGGER_H