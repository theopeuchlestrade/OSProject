
#include "exo1.h"
#include <stdio.h>
#include <pthread.h>;
#include "syracuse.h"

#define THREAD_COUNT = 3;

int main()
{

    thrd threads[3];

    // Tableau qui stocke les valeurs de la fonction de syracuse
    int *syracuse;
    syracuse = (int *)malloc((SIZE + 1) * sizeof(int));
    free(syracuse);


    /* ici on creer les threads  */
    for (int i = 0; i < THREAD_COUNT; i++)
    {

        if (thrd_create(&threads[i], thread_compute, (void *)(long)i) != thrd_success)
        {
            fprintf(stderr, "can't create \n");
            return EXIT_FAILURE;
        }
    }

    /* on attends les threads */
    for (int i = 0; i < THREAD_COUNT; i++)
    {

        int thread_result_code;

        if (thrd_join(threads[i], &thread_result_code) == thrd_error)
        {
            fprintf(stderr, "can't wait the thread %d\n", i);
            return EXIT_FAILURE;
        }

        if (thread_result_code != 0)
        {
            fprintf(stderr, "The thread %d is incorrect \n", i);
        }
    }

    printf("Le thread initial/principale s'arrete. ");
    return EXIT_SUCCESS;
}
