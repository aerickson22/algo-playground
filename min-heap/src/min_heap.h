#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct minheap_t minheap_t;

minheap_t* minheap_init(size_t data_size, int(*compare)(void* p1, void* p2));
minheap_t* minheap_make_heap(size_t data_size, void* array, size_t array_size, int(*compare)(void* p1, void* p2));
void minheap_destroy(minheap_t* mh);
int minheap_insert(void* x, minheap_t* mh);
void* minheap_extract_min(minheap_t* mh);
void* minheap_peek(minheap_t* mh);
int minheap_is_empty(minheap_t* mh);
char* minheap_to_string(const minheap_t* mh, void (*elem_to_string)(const void* elem, char* buf, size_t buf_size));

#endif
