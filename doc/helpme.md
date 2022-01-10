# Projet Programmation 2021/2022 | Julie BONNAIL & Thomas BOUYER

So here it is... Our programming project, used to parse a large xml database (learn more [here](https://dblp.org/)). Normally this entire project should be written in English (except for the [README](../README.md) and the [changelog](../changelog.md)) so we won't go into extensive usage details here. Instead, we will focus on explaining the main structures used, and how they can be exported to other projects. Such things that won't be found inside comments.

1. [vec_t, a vector class](#vec_t-a-vector-class)
2. [hset_t, a collection of unique elements](#hset_t-a-collection-of-unique-elements)
3. [dict_t, efficient key-value pairs storage](#dict_t-efficient-key-value-pairs-storage)
4. [pqueue_t, priority queue using a Fibonacci heap](#pqueue_t-priority-queue-using-a-fibonacci-heap)
5. [benches ? benches](#benches--benches)

## [vec_t](../includes/vec.h), a vector class

Maybe you are (or maybe you are not) familiar with the generic `Vec<T>` class prototype in C++. Well I missed it a lot. Here is an attempts at recreating it. Of course we do not have generic types in C so any `vec_t` just holds arbitrary `void *` pointers to elements.

It obviously has the obligatory `push` method, not that there are methods in C but anyway... You can push, pop, insert, get and set elements. Also in a concern of space management, any suppressed element will be replaced with the next push. So the order is not presserved, which kind of defeats the purpose of growable length arrays, and is a cheap optimisation anyway. Thinking of it right now, this might go away...

This structure does not have any dependencies, is c18 compliant and does not rely on any GNU extentions.

*   `vec_init(v)` takes an existing vector and initialises it

```c
/**
 * @brief initialize vector
 *
 * @param v vector
 */
void vec_init(vec_t *v);
```

*   `vec_new()` returns a brand new vector that you are going to want to free to comply with valgrind leak checks

```c
/**
 * @brief create a new vector
 *
 */
vec_t *vec_new(void);
```

*   `vec_pop(v)` returns and removes the last element of the vector

```C
/**
 * @brief delete and return the last element
 *
 * @param v vector
 * @return void*
 */
void *vec_pop(vec_t *v);
```

*   `vec_get_end(v)` returns the last element of the vector

```c
/**
 * @brief return the last element
 *
 * @param v vector
 * @return void*
 */
void *vec_get_end(vec_t *v);
```

*   `vec_get_at(v, ii)` returns the ii-th element of the vector (might beb NULL)

```c
/**
 * @brief get element at index
 *
 * @param v vector
 * @param index index
 * @return void*
 */
void *vec_get_at(vec_t *v, size_t index);
```

*   `vec_for_each(v, &cmp, &a)` will call `cmp(e, a)` for each non-NULL element `e` of the vector

```c
/**
 * @brief invoke callback on each element, stops if the callback returns
 * non-NULL
 *
 * @param v vector
 * @param fe for each callback
 * @param data callback data
 * @return void*
 */
void *vec_for_each(vec_t *v, for_each_callback_t *fe, void *data);
```

*   `vec_set_at(v, ii, &e)` will set the ii-th element of v to e

```c
/**
 * @brief set element at index
 *
 * @param v vector
 * @param index index
 * @param ptr pointer to element
 * @return void*
 */
void *vec_set_at(vec_t *v, int index, void *ptr);
```

*   `vec_delete_all(v, &dc)` will pop each element e of v and call `dc(e)` if e is non-NULL

```c
/**
 * @brief delete all elements, invoke delete_callback on each element
 *
 * @param v vector
 * @param dc delete callback
 */
void vec_delete_all(vec_t *v, delete_callback_t *dc);
```

*   `vec_delete_at(v, ii, &dc)` will delete the ii-th element of v and call the delete callback assuming that the element is non-NULL

```c
/**
 * @brief delete element at index and invoke delete_callback on it
 *
 * @param v vector
 * @param index index
 * @param dc delete callback
 */
void vec_delete_at(vec_t *v, size_t index, delete_callback_t *dc);
```

*   `vec_free(v)` will free the allocated memory of the vector (it will not free any of the elements though)

```c
/**
 * @brief free vector underlying structure.
 * It is user's responsability to free the elements.
 *
 * @param v vector
 */
void vec_free(vec_t *v);
```

*   `vec_used(v)` will return the number of entries of the vector

```c
/**
 * @brief return the number of entries in the vector
 *
 * @param v vector
 * @return size_t
 */
size_t vec_used(vec_t *v);
```

*   `vec_size(v)` will return the number of non-NULL entries of the vector

```c
/**
 * @brief return the number of allocated entries in the vector
 *
 * @param v vector
 * @return size_t
 */
size_t vec_size(vec_t *v);
```

*   `vec_push(v, &e)` will add e at the end of the vector

```c
/**
 * @brief push element to the end of the vector and return last slot index
 *
 * @param v vector
 * @param ptr pointer to element
 * @return size_t
 */
size_t vec_push(vec_t *v, void *ptr);
```

*   `vec_reverse(v)` will reverse the vector v in place

```c
/**
 * @brief reverse the order of the vector
 *
 * @param v vector
 */
void vec_reverse(vec_t *v);
```

*   `vec_print(v, &pc)` will call `pc(e)` for each non-NULL element e of v

```c
/**
 * @brief print each non-NULL element in the vector
 *
 * @param v vector
 * @param pc print callback
 */
void vec_print(vec_t *v, print_callback_t *pc);
```

*   `vec_qsort(v, &cmp)` will sort the vector using the cmp function. It may fail if there are NULL elements in the vector and if the cmp function does not explicitly handle those cases

```c
/**
 * @brief sort the vector.
 * User should probably remove all NULL elements before calling this.
 *
 * @param v vector
 * @param cmp compare callback
 */
void vec_qsort(vec_t *v, compare_fn_t *cmp);
```

*   `vec_to_array(v)` will return the array representation of the vector

```c
/**
 * @brief return the array representation of the vector
 *
 * @param v vector
 * @return void**
 */
void **vec_to_array(vec_t *v);
```

*   `vec_from_array(&arr, l)` will create a new vector from the provided array of length l

```c
/**
 * @brief make a new vector from an array
 *
 * @param array array of void*
 * @param size size of array
 * @return vec_t* - new vector
 */
vec_t *vec_from_array(void **array, size_t size);
```

*   `vec_copy(v)` will return a shallow copy of the vector

```c
/**
 * @brief copy vector (shallow copy of non-NULL elements)
 *
 * @param v vector
 * @return vec_t* - new vector
 */
vec_t *vec_copy(vec_t *v);
```

## [hset_t](../includes/hset.h), a collection of unique elements

The idea now comes from Python, the unknown little brother of the dictionnary object that holds unique elements and does not care about the order. At the time of writting, this `hset_t` structure hashes the pointer of the element so that if the object is modified after being inserted, it won't ever be inserted again.

It has obviously a push method. The contains method is really where the hash table magic kicks in. This structure can know if an element has already been stored in O(1)* time. Also I have worked around an iterator for this structure, which is kind of usefull to get through all stored elements in one go and free them all.

This structure currently needs [protocol.h](../includes/protocol.h) for debug assertions.

*   `hset_new()` will create a new empty hash set

```c
/**
 * @brief create a new hash set
 *
 * @return hset_t*
 */
hset_t *hset_new(void);
```

*   `hset_copy(s)` will return a new shallow copy of s

```c
/**
 * @brief return a new hash set.
 * Does not copy the elements.
 *
 * @param hset original hash set
 * @return hset_t* - copy of the original hash set
 */
hset_t *hset_copy(hset_t *hset);
```

*   `hset_free(s)` will free the allocated memory for s. It won't free any of its elements

```c
/**
 * @brief free a hash set underlying structure.
 * It is the caller's responsibility to free the items
 *
 * @param hset
 */
void hset_free(hset_t *hset);
```

*   `hset_push(s, &e)` will add e into s if e was previously not in s and return a corresponding error code

```c
/**
 * @brief add a new element to the hash set, does nothing if already present
 *
 * @param hset hash set
 * @param item new element
 * @return int - `-1` if error (bad item value),
 * `0` if already present (no change),
 * `1` if added (new element),
 * `2` if rehash did not work (set integrity compromised)
 */
int hset_push(hset_t *hset, void *item);
```

*   `hset_constains(s, &e)` will tell if the item is in the hash set or not

```c
/**
 * @brief test if an element is present in the hash set
 *
 * @param hset hash set
 * @param item item to check
 * @return int - 1 if present, 0 if not
 */
int hset_contains(hset_t *hset, void *item);
```

*   `hset_discard(s, &e)` will remove e from s if e is in s and returns a corresponding error code

```c
/**
 * @brief remove item from hash set, does nothing if not present
 *
 * @param hset hash set
 * @param item item to remove
 * @return int - `-1` if error (bad item value),
 * `0` if not found (no change),
 * `1` if removed (value removed),
 */
int hset_discard(hset_t *hset, void *item);
```

*   `hset_pop(s)` will remove an arbitrary element of the set

```c
/**
 * @brief return an arbitrary item from the hash set and remove it
 *
 * @param hset hash set
 * @return size_t - 0 if empty, otherwise the item
 */
size_t hset_pop(hset_t *hset);
```

*   `hset_nitems(s)` will return the number of unique elements in the set

```c
/**
 * @brief get the number of items in the hash set
 *
 * @param hset hash set
 * @return size_t - number of items
 */
size_t hset_nitems(hset_t *hset);
```

*   `hset_itr_new(s)` will create an iterator over s

```c
/**
 * @brief create a hashset iterator, advances to first value is available
 *
 * @param set hash set
 * @return hset_itr_t* - new iterator
 */
hset_itr_t *hset_itr_new(hset_t *set);
```

*   `hset_itr_value(itr)` will return the current valid value of the set iterator

```c
/**
 * @brief returns the value at the current index, it is the caller's
 * responsibility to cast the value
 *
 * @param itr iterator
 * @return size_t - value at current index
 */
size_t hset_itr_value(hset_itr_t *itr);
```

*   `hset_itr_hash_next(itr)` will tell if the iterator can advance to the next value or not

```c
/**
 * @brief return 1 is can advance, 0 otherwise
 *
 * @param itr iterator
 * @return int
 */
int hset_itr_has_next(hset_itr_t *itr);
```

*   `hset_itr_next(itr)` will advance the iterator to the next valid value if available

```c
/**
 * @brief check if iterator can advance, if so advances.
 * Returns current index if can advance and -1 otherwise
 *
 * @param itr iterator
 * @return size_t
 */
size_t hset_itr_next(hset_itr_t *itr);
```

*   `hset_itr_free(itr)` will free the allocated memory for the iterator only

```c
/**
 * @brief free the iterator's underlying structure.
 * Does not free the hash set
 *
 * @param itr iterator
 */
void hset_itr_free(hset_itr_t *itr);
```

*   `hset_itr_for_each(itr, &fe, &data)` will call `fe(e, data)` for each element of the set in an arbitrary order

```c
/**
 * @brief apply a function to each item in the hash set,
 * if the function returns non-null, the iteration is stopped
 * and the value is returned
 *
 * @details it is the caller's responsibility to reset the iterator
 * after calling this function
 *
 * @param itr iterator
 * @param fe function to apply
 * @param data data to pass to function
 */
void *hset_itr_for_each(hset_itr_t *itr, for_each_callback_t *fe, void *data);
```

*   `hset_itr_discard_all(itr, &dc)` will remove all elements from the set and call the delete callback on them

```c
/**
 * @brief discard all items from the hash set and invoke the delete callback
 *
 * @example hset_itr_discard_all(itr, free_item);
 *
 * @param itr iterator
 * @param dc delete callback
 */
void hset_itr_discard_all(hset_itr_t *itr, delete_callback_t *dc);
```

*   `hset_itr_reset(itr)` will reset the iterator to allow it to manually be iterated over

```c
/**
 * @brief reset the iterator to the beginning of the set
 *
 * @param itr iterator
 */
void hset_itr_reset(hset_itr_t *itr);
```

## [dict_t](../includes/dict.h), efficient key-value pairs storage

The logic big brother of the set, the dictionnary uses 2 hash tables in parallel to store keys and values at the same place. Again, the dictionnary hashes the pointers it receives and for efficiency concerns, only works with keys, assuming that it stores values in a similar way (which is does, thanks to the tests).

The methods here are basically the same as above, but with small tweaks to work with pairs of pointers. It also has an iterator which is mainly used to free all its elements in one line of code.

It does not depend on the hash set structure but does need [protocol.h](../includes/protocol.h).

*   `dict_new()` will return a new empty dictionary

```c
/**
 * @brief new dictionary
 *
 * @return dict_t*
 */
dict_t *dict_new(void);
```

*   `dict_free(d)` will free the memory of the dictionary but not of its keys nor elements

```c
/**
 * @brief free dictionary underlying structure.
 * It is caller responsibility to free the values if needed
 *
 * @param dict dictionary to free
 */
void dict_free(dict_t *dict);
```

*   `dict_push(d, &k, &v)` will add the `(k, v)` pair into dict assuming k was not in d, and return the corresponding error code

```c
/**
 * @brief add new key-value pair to dictionary.
 * If key already exists, the value is replaced.
 *
 * @param dict dictionary
 * @param key key
 * @param value value
 * @return int - `-1` if error (bad key value),
 * `0` if already present (value replaced),
 * `1` if added (new pair),
 * `2` if rehash did not work (dict integrity compromised)
 */
int dict_push(dict_t *dict, void *key, void *value);
```

*   `dict_get(d, &k)` will return the pointer to the value stored for the key k if it exists

```c
/**
 * @brief get value for given key
 *
 * @param dict dictionary
 * @param key key
 * @return size_t - value or 0 if key not found
 */
size_t dict_get(dict_t *dict, void *key);
```

*   `dict_discard(d, &k)` will remove both the key and its element from the dictionary without freeing their memory

```c
/**
 * @brief remove key-value pair from dictionary
 *
 * @param dict dictionary
 * @param item key of the pair to remove
 * @return int - -1 if error (bad key value),
 * `0` if not found (no change),
 * `1` if removed (key-value pair removed),
 */
int dict_discard(dict_t *dict, void *key);
```

*   `dict_copy(d)` will return a copy of d

```c
/**
 * @brief return a new dictionary
 * Does not copy any of the key-value pairs
 *
 * @param dict dictionary
 * @return dict_t* - copy of the original dictionary
 */
dict_t *dict_copy(dict_t *dict);
```

*   `dict_merge(d1, d2)` will push all pairs of d2 into d1

```c
/**
 * @brief merge the second dictionary into the first one.
 * Does not copy any of the key-value pairs.
 *
 * @param dict1 first dictionary
 * @param dict2 second dictionary
 * @return size_t* - number of items added to the first dictionary
 */
size_t dict_merge(dict_t *dict1, dict_t *dict2);
```

*   `dict_nitems(d)` will return the number of pairs stored in d

```c
/**
 * @brief get number of items in dictionary
 *
 * @param dict dictionary
 * @return size_t
 */
size_t dict_nitems(dict_t *dict);
```

*   `dict_itr_new(d)` will create a new iterator over d

```c
/**
 * @brief create a new iterator for dictionary, advance to first item
 *
 * @param dict dictionary
 * @return dict_itr_t*
 */
dict_itr_t *dict_itr_new(dict_t *dict);
```

*   `dict_itr_free(itr)` will free the iterator without freeing the dictionary

```c
/**
 * @brief free iterator only
 *
 * @param itr iterator
 */
void dict_itr_free(dict_itr_t *itr);
```

*   `dict_itr_key(itr)` will return a pointer to the current valid key

```c
/**
 * @brief get next key from iterator
 *
 * @param itr iterator
 * @return size_t - pointer to key
 */
size_t dict_itr_key(dict_itr_t *itr);
```

*   `dict_itr_value(itr)` will return a pointer to the current valid value

```c
/**
 * @brief get next value from iterator
 *
 * @param itr iterator
 * @return size_t - pointer to value
 */
size_t dict_itr_value(dict_itr_t *itr);
```

*   `dict_itr_has_next(itr)` will tell if the iterator can advance

```c
/**
 * @brief return 1 if can advance, 0 otherwise
 *
 * @param itr iterator
 * @return int - 0 if we reached the end, 1 otherwise
 */
int dict_itr_has_next(dict_itr_t *itr);
```

*   `dict_itr_next(itr)` will advance to the next valid pair if available

```c
/**
 * @brief check if iterator can advance, if so advances.
 * Returns current index if can advance and -1 otherwise
 *
 * @param itr iterator
 * @return size_t
 */
size_t dict_itr_next(dict_itr_t *itr);
```

*   `dict_itr_reset(itr)` will reset the iterator to alow it to ba manually iterated over

```c
/**
 * @brief reset the iterator to the beginning of the dictionary
 *
 * @param itr iterator
 */
void dict_itr_reset(dict_itr_t *itr);
```

*   `dict_itr_for_each(itr, &fe1n &d1, &fe2, &d2)` will call `fe1(k, d1)` on each key k and `fe2(v, d2)` on each value v providing that the data involved is non-NULL

```c
/**
 * @brief iterate over dictionary and call the callback for each key-value pair
 * if the function returns non-null, the iteration is stopped
 * and the value is returned
 *
 * @details it is the caller's responsibility to reset the iterator
 * after calling this function
 *
 * @param itr dictionary iterator
 * @param fe1 function to call for each key
 * @param data1 data to pass to callback
 * @param fe2 function to call for each value
 * @param data2 data to pass to callback
 * @return void* - data returned by callback if non-null
 */
void *dict_itr_for_each(dict_itr_t *itr, for_each_callback_t *fe1, void *data1,
                        for_each_callback_t *fe2, void *data2);
```

*   `dict_itr_discard_all(itr, &dc1, &dc2)` will remove all pairs and invoke corresponding delete callback on each one

```c
/**
 * @brief discard all key-value pairs from dictionary
 *
 * @param itr dictionary iterator
 * @param dc1 delete callback for each key
 * @param dc2 delete callback for each value
 */
void dict_itr_discard_all(dict_itr_t *itr, delete_callback_t *dc1,
                          delete_callback_t *dc2);
```

## [pqueue_t](../includes/pqueue.h), priority queue using a Fibonacci heap

To greatly accelerate the Dijkstra algorithm, we need an efficient priority queue. This implementation uses a Fibonacci heap, allowing it to reach the following time complexity

| Operation    | Average time complexity |
| ------------ | ----------------------- |
| Insert       | Θ(1)                    |
| Find-min     | Θ(1)                    |
| Delete-min   | O(log n)                |
| Decrease-key | Θ(1)                    |
| Merge        | Θ(1)                    |

There is a twist though. Because we do not want the user to struggle with `heap_node_t`, the priority queue stores all correspondances between elements we insert, and the node associated with it in a dictionary.

This implementation requires [dict.h](../includes/dict.h) and its requirements.

```c
/**
 * @brief create a new priority queue
 *
 * @return pqueue_t*
 */
pqueue_t *pqueue_new();
```

*   `pqueue_new()` will create an empty priority queue

```c
/**
 * @brief get total node in the priority queue
 *
 * @param pq priority queue
 * @return size_t
 */
size_t pqueue_size(pqueue_t *pq);
```

*   `pqueue_size(p)` will return the number of elements in the priority queue

```c
/**
 * @brief get the minimum element of the priority queue
 *
 * @param pq priority queue
 * @return void*
 */
void *pqueue_find_min(pqueue_t *pq);
```

*   `pqueue_find_min(p)` will return the minimum element in constant time

```c
/**
 * @brief get the minimum element of the priority queue and remove it.
 * The node is freed but the element is still accessible
 *
 * @param pq priority queue
 * @return void*
 */
void *pqueue_pop_min(pqueue_t *pq);
```

*   `pqueue_push(p, &e, k)` will add e to the priority queue according to some key k

```c
/**
 * @brief insert an element into the priority queue.
 * Does nothing if the element is already present
 *
 * @param pq priority queue
 * @param element element to insert
 * @param key priority of the element
 * @return int - `-1` if error (bad key value),
 * `0` if already present (no change),
 * `1` if added (new entry),
 * `2` if rehash did not work (priority queue integrity compromised)
 */
int pqueue_push(pqueue_t *pq, void *element, int key);
```

*   `pqueue_decrease_key(p, &e, k)` will affect a new key to an existing element and return a corresponding error code

```c
/**
 * @brief decrease the priority of an element
 *
 * @param pq priority queue
 * @param element element to decrease the priority
 * @param new_key new priority
 * @return int - 1 if success, 0 if element does have a lower priority,
 * -1 if element does not exist
 */
int pqueue_decrease_key(pqueue_t *pq, void *element, int new_key);
```

*   `pqueue_merge(p1, p2)` will merge p2 into p1 and reset p2

```c
/**
 * @brief merge second priority queue into the first one.
 * The second priority queue is reset.
 * Due to limitations, user should be aware that duplicated nodes
 * may cause the first priority queue to become corrupted.
 *
 * @note Do not use this function please.
 *
 * @param pq1 first priority queue
 * @param pq2 second priority queue
 */
void pqueue_merge(pqueue_t *pq1, pqueue_t *pq2);
```

*   `pqueue_free(p)` will free the memory used for p and it dictionary

```c
/**
 * @brief free the priority queue and all its nodes (might be expensive)
 *
 * @param pq priority queue
 */
void pqueue_free(pqueue_t *pq);
```

## benches ? benches

So here benches will be performed on 2 different computers (one being a remote). They will be named after their cpu. So the mobile one has : Ryzen 7 5800hs (3200 MHz base clock speed, 4.6 on boost, 16MB L3), NVidia rxt 3060 (120W, 6Go gddr6, 192 bits), 16Go dual ddr4 ram, 512GO nvme pcle 4 ssd (4200 Mo average speed seek). The battlestation one has : Ryzen 9 5950x (3600 MHz base clock speed, 4.9 on boost, 7.3 when overclocked, 64MB L3), NVidia rtx 3090 (350W, CUDA cores 10496, 24Go gddr6x, 384 bits), 128Go quad ddr4 ram, 3To nvme pcle 4 ssd (8100 MO average speed seek). Given range represent when on performance mode and boost or overclocked (average are made on eta 200 runs).

| Test performed                 | average time on mobile | average time on desktop |
| ------------------------------ | ---------------------- | ----------------------- |
| empty parse (without writting) | 9.1 - 11.5 s           | 3.35 - 7.71 s           |
| check rule in tests            | 0.8 - 2.1 s            | 0.21 - 1.15 s           |
| cov rule in tests              | 1.1 - 2.2 s            | 0.22 - 1.15 s           |
