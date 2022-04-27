
#include "exo1.h"
#include <stdio.h>
#include <pthread.h>
#include "syracuse.h"
#include "cache.h"
#include <assert.h>
#include <unistd.h>


void *thread_compute(void *arg) {

    syracuse_args_t  *range = (syracuse_args_t *) arg;

    printf("Thread : %d will work on range %d, %d \n", (int) getpid(), range->start, range->end);

    int i = range->start;

    for (range->start; i < range->end; i++) {
        printf("thread %d is computing : %d\n", range->thread_id, i );
        range->tab[i] = get_time_of_flight_recursive(i,range->cache);

        // sleep(1) ;
    }

    return NULL;
}

int main() {

    // Tableau qui stocke les valeurs de la fonction de syracuse
    int *syracuse;
    syracuse = (int *) calloc((SIZE + 1), sizeof(int)); // init a 0 ;


    // assert( syracuse != NULL );


    /* prepare cache  */
    cache_t cache;
    cache_init(&cache);


    pthread_t thread_1; // 1 to 10
    pthread_t thread_2; // 11 to 20
    pthread_t thread_3; // 21 to 30

    syracuse_args_t first = {
            .thread_id =  1,
            .cache = &cache,
            .tab = syracuse,
            .start = 1,
            .end = 10
    };

    syracuse_args_t sec = {
            .thread_id =  2,
            .cache = &cache,
            .tab = syracuse,
            .start = 11,
            .end = 20
    };

    syracuse_args_t third = {
            .thread_id =  3,
            .cache = &cache,
            .tab = syracuse,
            .start = 21,
            .end = 30
    };

    printf("pid of main is : %d\n", (int) getpid());


    /* Create threads */
    pthread_create(&thread_1, NULL, &thread_compute, &first);
    pthread_create(&thread_2, NULL, &thread_compute, &sec);
    pthread_create(&thread_3, NULL, &thread_compute, &third);

    /* Wait threads */

    pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);
    pthread_join(thread_3, NULL);

    printf("End of threads \n");

    // display_syracuse(syracuse);

    free(syracuse);
    cache_destroy(&cache);

    return EXIT_SUCCESS;
}
