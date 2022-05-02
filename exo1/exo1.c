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

        // sleep(1);
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
        syracuse = (int *)calloc((input_size), sizeof(int)); // init a 0 ;

        // assert( syracuse != NULL );

        /* prepare cache  */
        cache_t cache;
        cache_init(&cache);

        //(int)(input_size/NB_THREAD)
        int USABLE_THREADS = (int)((input_size - 1) / NB_THREAD) + 1 ;
        pthread_t thread[USABLE_THREADS]; // 1 to 10 , 11 to 20 , 21 to 30

        syracuse_args_t *schema = calloc(USABLE_THREADS, sizeof(syracuse_args_t));
        // Init threads args
        for (int num_thread = 0; num_thread < USABLE_THREADS; num_thread++)
        {
            schema[num_thread].thread_id = num_thread,
            schema[num_thread].cache = &cache,
            schema[num_thread].tab = syracuse,
            schema[num_thread].start = num_thread * 10 + 1,
            schema[num_thread].end = (num_thread + 1) * 10;
        }

        printf("pid of main is : %d\n", (int)getpid());

        /* Create threads */
        for (int i = 0; i < USABLE_THREADS; i++)
        {
            pthread_create(&thread[i], NULL, &thread_compute, &schema[i]);
        }

        /* Wait threads */
        for (int i = 0; i < USABLE_THREADS; i++)
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
