

#ifndef OSPROJECT_SYRACUSE_H
#define OSPROJECT_SYRACUSE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define SIZE 1000
#define NB_THREAD 10

/*Exemple de structure contenant les arguments passes a chaque thread
 * Chaque thread devrai calculer syracuse de start jusqu'à end
 */
typedef struct syracuse_args
{
    int start;
    int end;
} syracuse_args_t;

void funSyracuse(int n, int *tab, int table_size);
int thread_compute(void *data);

#endif // OSPROJECT_SYRACUSE_H
