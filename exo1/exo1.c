#include "exo1.h"
#include "syracuse.h"
#include "utils.h"

#include "cache.h"
#include <stdio.h>
#include <pthread.h>
#include <assert.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define free(x) printf("%s:%d free %p\n", __FILE__, __LINE__,x); free(x);

void *thread_compute(void *arg)
{

    syracuse_args_t *range = (syracuse_args_t *)arg;

    // printf("Thread : %d will work on range %d, %d \n", (int)getpid(), range->start, range->end);

    int i = range->start;

    while(i <= range->end)
    {

        //debug("thread %d is computing : %d\n", range->thread_id, i);
        range->tab[i] = get_time_of_flight_recursive(i, range->cache);
        i++;
    }

    return NULL;
}

int main(int argc, char *argv[])
{
    // check if debug is enable

    if (argc == 2)
    {
        int input_size = atoi(argv[1]);
        printf("SIZE = %d\n", input_size);

        /* prepare cache  */
        cache_t cache;
        cache_init(&cache);

        int nb_thread = (int) (input_size / NB_THREAD) + 1;
        if(nb_thread > NB_THREAD) nb_thread = NB_THREAD;

        pthread_t thread[nb_thread];
        
        //Get number of iterations
        int nb_iteration = 0; 
        if(input_size %2 == 1) nb_iteration = (int) (input_size + 1)/nb_thread;
        else nb_iteration = (int) input_size/nb_thread; 

        // assert( syracuse != NULL );
        int *syracuse = (int *)calloc((input_size + 1), sizeof(int)); // init a 0 ;
        
        syracuse_args_t *schema = calloc(nb_thread, sizeof(syracuse_args_t));
        // Init threads args
        for (int num_thread = 0; num_thread < nb_thread; num_thread++)
        {
            schema[num_thread].thread_id = num_thread;
            schema[num_thread].cache = &cache;
            schema[num_thread].tab = syracuse;
            schema[num_thread].start = nb_iteration * num_thread + 1;
            if (num_thread == nb_thread - 1) {
                schema[num_thread].end = input_size;
            }
            else {
                schema[num_thread].end = nb_iteration * (num_thread + 1);
            }
            debug("Num schema[%d] : start = %d, end = %d\n", num_thread, schema[num_thread].start, schema[num_thread].end);
        }

        // debug("pid of main is : %d\n", (int)getpid());

        /* Create threads */
        for (int num_thread = 0; num_thread < nb_thread; num_thread++)
        {
            pthread_create(&thread[num_thread], NULL, &thread_compute, &schema[num_thread]);
            //debug("Creating the thread %d.\n", num_thread);
        }


        /* Wait threads */
        for (int num_thread = 0; num_thread < nb_thread; num_thread++)
        {
            pthread_join(thread[num_thread], NULL);
        }

        debug("End of threads \n");

        //display_syracuse(syracuse);

        for(int nb = 0; nb < input_size+1; nb++) printf("Syracuse de %d est %d.\n", nb, syracuse[nb]);
        
        free(syracuse);
        free(schema);
        cache_destroy(&cache);
    }
    else
    {

        debug("Missing args format size syracuse\n");
        debug("Exemple : ./exo1 10\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
