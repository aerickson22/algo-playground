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
	float load_factor;
	int(*compare)(void* k1, void* k2);
	size_t(*hash)(void* kkey);
	struct node_t** data;
};

struct hashtable_t* hashtable_init(size_t key_size, size_t value_size, int(*compare)(void* k1, void* k2), size_t(*hash)(void* key)){
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
	out->key_data_size = key_size;
	out->value_data_size = value_size;
	out->compare = compare;
	out->hash = hash;
	return out;
}

void hashtable_destory(struct hashtable_t* ht){
	free(ht->data);
	free(ht);
}

void hashtable_put(void* key, void* value, struct hashtable_t* ht){
	//todo
}

void* hashtable_get(void* key, struct hashtable_t* ht){
	//todo
	return NULL;
}

void* hashtable_remove(void* key, struct hashtable_t* ht){
	//todo
	return NULL;
}

