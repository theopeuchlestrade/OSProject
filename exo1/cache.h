
#ifndef OSPROJECT_CACHE_H
#define OSPROJECT_CACHE_H

#include <semaphore.h>

typedef struct cache_entry {
    int key;
    int val;
} cache_entry_t;

typedef struct cache {
    sem_t lock;
    int lenght;
    cache_entry_t *entries;

} cache_t;


void cache_set(cache_t *cache, int key, int val);

void cache_del(cache_t *cache, int key);

int cache_get(cache_t *cache, int key);

void cache_init(cache_t *cache);

void cache_destroy(cache_t *cache);

#endif //OSPROJECT_CACHE_H
