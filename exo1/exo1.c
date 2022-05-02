#include "exo1.h"
#include "syracuse.h"
#include "cache.h"
#include <stdio.h>
#include <pthread.h>
#include <assert.h>
#include <unistd.h>

void *thread_compute(void *arg)
{

    syracuse_args_t *range = (syracuse_args_t *)arg;

    printf("Thread : %d will work on range %d, %d \n", (int)getpid(), range->start, range->end);

    int i = range->start;
    printf("Valeur de i : %d\n",i);
    for (range->start; i < range->end; i++)
    {
        printf("thread %d is computing : %d\n", range->thread_id, i);
        range->tab[i] = get_time_of_flight_recursive(i, range->cache);

        sleep(1);
    }

    return NULL;
}

int main(int argc, char *argv[])
{

    if (argc == 2)
    {

        int input_size = atoi(argv[1]);
        printf("SIZE = %d\n", input_size);

        int *syracuse;
        syracuse = (int *)calloc((input_size + 1), sizeof(int)); // init a 0 ;

        // assert( syracuse != NULL );

        /* prepare cache  */
        cache_t cache;
        cache_init(&cache);

        //(int)(input_size/NB_THREAD)
        pthread_t thread[NB_THREAD]; // 1 to 10 , 11 to 20 , 21 to 30

        syracuse_args_t *schema = calloc(sizeof(syracuse_args_t), NB_THREAD);
        // Init threads args NIGGA
        for (int i = 0; i < NB_THREAD; i++)
        {
            schema[i].thread_id = i,
            schema[i].cache = &cache,
            schema[i].tab = syracuse,
            schema[i].start = i * 10 + 1,
            schema[i].end = (i + 1) * 10;
        }

        printf("pid of main is : %d\n", (int)getpid());

        /* Create threads */
        for (int i = 0; i < NB_THREAD; i++)
        {
            pthread_create(&thread[i], NULL, &thread_compute, &schema[i]);
        }

        /* Wait threads */
        for (int i = 0; i < NB_THREAD; i++)
        {
            pthread_join(thread[i], NULL);
        }

        printf("End of threads \n");

        // display_syracuse(syracuse);

        free(syracuse);
        free(schema);
        cache_destroy(&cache);
    }
    else
    {

        printf("Missing args format size syracuse\n");
        printf("Exemple : ./exo1 10\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
