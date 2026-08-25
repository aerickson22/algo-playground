#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "min_heap.h"

int compare_int(void* p1, void* p2){
    return (*(int*)p1) - (*(int*)p2);
}

void int_to_string(const void* elem, char* buf, size_t buf_size) {
    snprintf(buf, buf_size, "%d", *(const int*)elem);
}

int main(){
    srand(time(NULL));
    minheap_t* heap;
    int arr[10];
    for(int i = 0; i < 10; i++){
        int num = ((rand() % (999)) + 1);
        arr[i] = num;
    }
    if(!(heap = minheap_make_heap(sizeof(int), arr, 10, compare_int))){
        return -1;
    }
    char* str = minheap_to_string(heap, int_to_string);
    if (str) {
        printf("Min-Heap array representation:\n%s\n", str);
    }
    minheap_destroy(heap);
    return 0;
}
