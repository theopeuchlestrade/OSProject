#include "syracuse.h"
#include <pthread.h>


// int pthread_create(pthread_t *thread, pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);

// Fonction réalisant la suite de Syracuse à partir de l'entier n.
void funSyracuse(int n, int *tab, int table_size)
{
    tab[0] = table_size;
    int i = 1;
    printf("%d =>  %d\n", 0, tab[0]);

    while (n > 1)
    {
        if (n % 2 == 0)
        {
            n /= 2; // quotient
            tab[i] = n;
            printf("%d =>  %d\n", i, n);
            i++;
        }
        else
        {
            n = 3 * n + 1;
            tab[i] = n;
            printf("%d =>  %d\n", i, n);
            i++;
        }
    }
}

int flight_time(int *tab) {

    int step = 0 ;
    int index = 0 ;

    while (tab[index] != 1 ) {
        step++;
        index++;
    }

    return step;
}
