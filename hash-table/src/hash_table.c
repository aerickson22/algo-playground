#include "hash_table.h"

#define DEFAULT_CAPACITY 10
#define DEFAULT_LOAD_FACTOR 0.75f
#define HASHTABLE_OK 0
#define HASHTABLE_ERROR -1

struct node_t{
	char* key;
	char* value;
	struct node* next;
	struct node* previous;
};

struct hashtable_t{
	size_t capacity;
	size_t size;
	size_t key_data_size;
	size_t value_data_size;
	int(*compare)(void* k1, void* k2);
	float load_factor;
	struct node_t** data;
};

size_t _hash(void* key, hashtable_t* ht){
	unsigned long int hash_value = 5381;
	int c;
	while(c = *((char*)key++)){
		hash_value = ((hash_value << 5) + hash_value) + c;
	}
	return (size_t)hash_value % ht->capacity;
}

struct hashtable_t* hashtable_init(size_t key_size, size_t value_size, int(*compare)(void* k1, void* k2)){
	hashtable_t* out;
	if(!(out = malloc(sizeof(*out)))){
		return NULL;
	}
	struct node_t** out_data;
	if(!(out_data = malloc(sizeof(*out_data) * DEFAULT_CAPACITY))){
		free(out);
		return NULL;
	}
	out->data = out_data;
	out->capacity = DEFAULT_CAPACITY;
	out->load_factor = DEFAULT_LOAD_FACTOR;
	out->size = 0;
	out->compare = compare;
	out->key_data_size = key_size;
	out->value_data_size = value_size;
	return out;
}

void hashtable_destory(struct hashtable_t* ht){
	free(ht->data);
	free(ht);
}

int hashtable_put(void* key, void* value, struct hashtable_t* ht){
	struct node_t* curr = ht->data + (_hash(key, ht) * sizeof(struct node_t));
	if(!curr){
		if(!(curr = malloc(sizeof(*curr)))){
			return HASHTABLE_ERROR;		
		}
		curr->next = NULL;
		curr->key = key;
		curr->value = value;
	}else{
		while(curr->next){
			curr = curr->next;
		}
		curr->next = NULL;
		curr->key = key;
		curr->value = value;
	}
	return HASHTABLE_OK;
}

void* hashtable_get(void* key, struct hashtable_t* ht){
	void* value = NULL;
	struct node_t* curr = ht->data + (_hash(key, ht) * sizeof(struct node_t));
	while(curr->next){
		if(curr->key){
			
		}
	}
	return value;
}

void* hashtable_remove(void* key, struct hashtable_t* ht){
	//todo
	return NULL;
}

