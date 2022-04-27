

#ifndef OSPROJECT_SYRACUSE_H
#define OSPROJECT_SYRACUSE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "cache.h"

#define SIZE 1000
#define NB_THREAD 10


typedef struct syracuse_args {
    int thread_id ;
    cache_t *cache;
    int *tab;
    int start;
    int end;
} syracuse_args_t;

int get_time_of_flight(int n, int *tab, int table_size);
int get_time_of_flight_recursive(int n, cache_t *cache);

void display_syracuse(int *tab);

#endif // OSPROJECT_SYRACUSE_H
