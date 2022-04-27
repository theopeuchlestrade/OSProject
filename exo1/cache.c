#include "cache.h"
#include <string.h>
#include <stdlib.h>


static cache_entry_t *cache_entry_find(cache_t *cache, int key) {

    for (int i = 0; i < cache->lenght; ++i) {
        cache_entry_t *entry = &cache->entries[i];

        if (entry->key == key) {
            return entry;
        }
    }

    return NULL; // err
}


int cache_get(cache_t *cache, int key) {
    sem_wait(&cache->lock);

    cache_entry_t *entry = cache_entry_find(cache, key);

    sem_post(&cache->lock);

    if (entry) {
        return entry->val;
    }
    return -1;
}

void cache_set(cache_t *cache, int key, int val) {

    sem_wait(&cache->lock);

    cache_entry_t *entry = cache_entry_find(cache, key);

    if (entry) {
        entry->val = val;
    } else {

        cache_entry_t *new_entries = calloc(cache->lenght + 1, sizeof(cache_entry_t));

        if (cache->entries) {
            memcpy(new_entries, cache->entries, cache->lenght * sizeof(cache_entry_t));
            free(cache->entries);
        }
        cache->entries = new_entries;

        entry = &cache->entries[cache->lenght];

        entry->key = key;
        entry->val = val;

        cache->lenght++;

    }

    sem_post(&cache->lock);

}

void cache_del(cache_t *cache, int key) {
    sem_wait(&cache->lock);

    cache_entry_t *entry = cache_entry_find(cache, key);

    if (entry) {

        memmove(entry, entry + 1, entry - cache->entries);

        cache->lenght--;

    }
    sem_post(&cache->lock);
}


void cache_init(cache_t *cache) {

    sem_init(&cache->lock, 0, 1);

    cache->lenght = 0;
    cache->entries = NULL;
}

void cache_destroy(cache_t *cache) {
    sem_close(&cache->lock);
    free(cache->entries);
}