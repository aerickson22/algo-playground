/**
 * @file hash_table.h
 * @brief Generic hash table (hash map) interface.
 *
 * This header declares a generic, opaque hash table type capable of storing
 * arbitrary fixed-size keys and values. The caller supplies comparison and
 * hashing functions appropriate for the key type at initialization time,
 * allowing the same implementation to be reused for any key/value types.
 *
 * Typical usage:
 * @code
 * hashtable_t* ht = hashtable_init(sizeof(int), sizeof(int),
 *                                  int_compare, int_hash);
 * int key = 42, value = 100;
 * hashtable_put(&key, &value, ht);
 * int* result = (int*)hashtable_get(&key, ht);
 * hashtable_destory(ht);
 * @endcode
 */

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdlib.h>
#include <stdint.h>

/**
 * @brief Opaque hash table type.
 *
 * The internal structure is not exposed to callers; all interaction with
 * the hash table must go through the functions declared in this header.
 */
typedef struct hashtable_t hashtable_t;

/**
 * @brief Create and initialize a new hash table.
 *
 * Allocates a new hash table configured to store keys and values of the
 * given fixed sizes. The caller must provide functions for comparing keys
 * and computing their hash values, since the table itself has no knowledge
 * of the underlying key type.
 *
 * @param key_size   Size, in bytes, of a single key.
 * @param value_size Size, in bytes, of a single value.
 *
 * @return Pointer to a newly allocated hashtable_t, or NULL on allocation
 *         failure.
 *
 * @note The caller is responsible for eventually calling hashtable_destory()
 *       to free the returned table.
 */
hashtable_t* hashtable_init(size_t key_size, size_t value_size, int(*compare)(void* k1, void* k2));

/**
 * @brief Destroy a hash table and free all associated memory.
 *
 * Releases all internal storage used by the hash table, including any
 * stored keys and values. After this call, @p ht must not be used again.
 *
 * @param ht Pointer to the hash table to destroy.
 *
 * @note The function name preserves the original spelling
 *       ("hashtable_destory") from the source header; consider renaming to
 *       "hashtable_destroy" if you control the implementation, since
 *       renaming later would be a breaking API change for callers.
 */
void hashtable_destory(hashtable_t* ht);

/**
 * @brief Insert or update a key/value pair in the hash table.
 *
 * If @p key already exists in the table (as determined by the table's
 * compare function), its associated value is overwritten with @p value.
 * Otherwise, a new entry is inserted.
 *
 * @param key   Pointer to the key to insert or update. The key data is
 *              copied into the table (key_size bytes, as set at init).
 * @param value Pointer to the value to associate with the key. The value
 *              data is copied into the table (value_size bytes).
 * @param ht    Hash table to insert into.
 *
 * @return integer signaling OK(0) state or ERROR(-1) state
 */
int hashtable_put(void* key, void* value, hashtable_t* ht);

/**
 * @brief Retrieve the value associated with a key.
 *
 * @param key Pointer to the key to look up.
 * @param ht  Hash table to search.
 *
 * @return Pointer to the stored value if @p key is found, or NULL if the
 *         key does not exist in the table.
 *
 * @warning The returned pointer refers to memory owned by the hash table;
 *          do not free it directly, and treat it as invalid after any
 *          subsequent call that modifies or destroys the table.
 */
void* hashtable_get(void* key, hashtable_t* ht);

/**
 * @brief Remove a key/value pair from the hash table.
 *
 * Removes the entry associated with @p key, if present.
 *
 * @param key Pointer to the key to remove.
 * @param ht  Hash table to remove from.
 *
 * @return Pointer to the removed value, or NULL if the key was not found.
 *
 * @warning Check the implementation to confirm whether the returned pointer
 *          remains valid after removal (e.g. whether ownership transfers to
 *          the caller) or whether it is freed internally; this affects
 *          whether the caller must free it.
 */
void* hashtable_remove(void* key, hashtable_t* ht);

#endif /* HASH_TABLE_H */
