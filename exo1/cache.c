#include "cache.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

static cache_entry_t *cache_entry_find(cache_t *cache, int key) {

    for (int i = 0; i < cache->length; ++i) {
        cache_entry_t *entry = &cache->entries[i];

        if (entry->key == key) {
            return entry;
        }
    }

    return NULL; // err
}


int cache_get(cache_t *cache, int key) {
    sem_wait(cache->lock);

    cache_entry_t *entry = cache_entry_find(cache, key);

    int ret = -1 ;
    if (entry) {
        ret = entry->val;
    }

    sem_post(cache->lock);

    return  ret;
}

void cache_set(cache_t *cache, int key, int val) {

    if (sem_wait(cache->lock) == -1 ) {
        perror("sem_lock");
        abort();
    }

    int l ;
    sem_getvalue(cache->lock, &l);


    cache_entry_t *entry = cache_entry_find(cache, key);

    if (entry) {
        entry->val = val;
    } else {

        cache_entry_t *new_entries = calloc(cache->length + 1, sizeof(cache_entry_t));

        if (cache->entries) {
            memcpy(new_entries, cache->entries, cache->length * sizeof(cache_entry_t));
            free(cache->entries);
        }
        cache->entries = new_entries;

        entry = &cache->entries[cache->length];

        entry->key = key;
        entry->val = val;

        cache->length++;

    }
    sem_post(cache->lock);

}

void cache_del(cache_t *cache, int key) {
    sem_wait(cache->lock);

    cache_entry_t *entry = cache_entry_find(cache, key);

    if (entry) {

        memmove(entry, entry + 1, entry - cache->entries);

        cache->length--;

    }
    sem_post(cache->lock);
}


void cache_init(cache_t *cache) {
  
    sem_unlink(NAME_SEMAPHORE);  // Force to remove sem from system

    errno = 0 ;
    cache->lock = sem_open(NAME_SEMAPHORE, O_RDWR|O_CREAT|O_EXCL, 0777, 1);
    if(cache->lock == SEM_FAILED){
        printf("Merde !\n");
    }
    
    if (errno) {
        perror("sem_open");
        abort();
    }
    cache->length = 0;
    cache->entries = NULL;
}

void cache_destroy(cache_t *cache) {
    // sem_close(cache->lock);

    // Close semaforo
    if (sem_close(cache->lock) == -1) {
        perror("Error at sem_close()!\n");
        exit(EXIT_FAILURE);
    }


    if (sem_unlink(NAME_SEMAPHORE) == -1) {
        perror("Error at sem_unlink()!\n");
        printf("Error: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    free(cache->entries);
}

void cache_dump(cache_t *cache) {
    printf("[ cache dump ] \n") ;
    for (int i = 0; i < cache->length; ++i) {
        cache_entry_t *entry = &cache->entries[i];
        printf("[ %5d | %5d ]\n", entry->key, entry->val);
    }
}