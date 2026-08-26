#include <stdio.h>

#include "hash_table.h"

int compare_int(void* i1, void* i2){
	return *((int*)i1) - *((int*)i2);
}

int main(){
	hashtable_t* ht;	 
	if(!(ht = hashtable_init(sizeof(int), sizeof(char**), compare_int))){
		return -1;
	}
	int num = 45;
	int* num_ptr = &num;
	char** name = "Sponge-Bob\n";

	if(hashtable_put(num_ptr, name, ht)){
		return -1;
	}
	hashtable_destory(ht);
	return 1;
}
