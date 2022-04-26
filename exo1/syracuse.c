#include <syracuse.h>

int thread_compute(void *data) // pass struc
{

    syracuse_args args = (syracuse_args)data;

    // do the math here ....

    printf("Thread %ld termine. \n", thread_index);
    return thrd_success;
}

// int pthread_create(pthread_t *thread, pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);

// Fonction réalisant la suite de Syracuse à partir de l'entier n.
int funSyracuse(int n, int tab[])
{
    int i = 0;
    int x = n;
    while (n != 0)
    {
        if (x % 2 == 0)
        {
            x = x / 2;
            tab[i] = x;
            i++;
        }
        else if (x % 2 != 0)
        {
            x = 3 * x + 1;
            tab[i] = x;
            i++;
        }
    }
    return -1;
}
