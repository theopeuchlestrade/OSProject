

#ifndef OSPROJECT_SYRACUSE_H
#define OSPROJECT_SYRACUSE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "cache.h"

#define SIZE 1000
#define NB_THREAD 10


typedef struct syracuse_args
{
    cache_t cache;
    int *tab;
    int start;
    int end;
} syracuse_args_t;

void funSyracuse(int n, int *tab, int table_size);
int flight_time(int *tab);

#endif // OSPROJECT_SYRACUSE_H
