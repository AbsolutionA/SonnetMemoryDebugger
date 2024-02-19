#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "../include/memorydebugger.h"

#define S_DEBUG_MEMORY_MAX_LIST_SIZE 10000

typedef struct sDebugMemoryInfo {
    void        *address;
    uint32_t    line;
    uint32_t    size;
    char        *file;
    uint8_t     free_status;
    char        *free_file;
    uint32_t    free_line;
    uint32_t    count;
} sDebugMemoryInfo;


static sDebugMemoryInfo list[S_DEBUG_MEMORY_MAX_LIST_SIZE];
static uint32_t page_iterator = 0;

static void s_debug_memory_info_keeper(sDebugMemoryInfo *data) {
    if (page_iterator < S_DEBUG_MEMORY_MAX_LIST_SIZE) {
        list[page_iterator] = *data;
        page_iterator++;
    }
    else {
        fprintf(stderr, "The memory list limit has been reached!\n");
    }
}

void *s_debug_memory_malloc(uint32_t size, char *file, uint32_t line) {
    sDebugMemoryInfo data;
    data.address = malloc(size);
    data.line = line;
    data.file = file;
    data.size = size;
    data.free_status = 0;
    data.free_file = "Not yet freed!";
    data.free_line = 0;
    data.count = page_iterator + 1; 
    s_debug_memory_info_keeper(&data);

    return data.address;
}

void s_debug_memory_free(void *buffer, char *file, uint32_t line) {
    if (page_iterator == 0) {
        fprintf(stderr, "Nothing is allocated!");
    }
    else {
        free(buffer);
        for (uint32_t i = 0; i < page_iterator; i++) {
            if (list[i].address == buffer) {
                list[i].free_status = 1;
                list[i].free_file = file;
                list[i].free_line = line;
            }
        }
    }
}

void s_debug_memory_info_print() {
    for (uint32_t i = 0; i < page_iterator; i++) {
        fprintf(stderr, "[%d]Memory address: %p\n"
                        "File: %s\n"
                        "Line: %d\n"
                        "Size: %d\n"
                        "Has it been freed?: %d\n"
                        "Free file: %s\n"
                        "Free line: %d\n\n",
                        list[i].count, list[i].address,
                        list[i].file, list[i].line, 
                        list[i].size, list[i].free_status, 
                        list[i].free_file, list[i].line);
    }
}