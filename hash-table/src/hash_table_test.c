#include <stdio.h>

#include "hash_table.h"

int compare_int(void* i1, void* i2){
	return *((int*)(i1)) - *((int*)(i2));
}

size_t hash_int(void* key){
	return *((int*)(key)) % 10;
}	

int main(){
	hashtable_t* ht;	 
	if(!(ht = hashtable_init(sizeof(int), sizeof(int), compare_int, hash_int))){
		return -1;
	}
	hashtable_destory(ht);
	return 1;
}
