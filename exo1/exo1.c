#include "exo1.h"
#include "syracuse.h"
#include "cache.h"
#include <stdio.h>
#include <pthread.h>
#include <assert.h>
#include <unistd.h>


void *thread_compute(void *arg) {

    syracuse_args_t *range = (syracuse_args_t *) arg;

    printf("Thread : %d will work on range %d, %d \n", (int) getpid(), range->start, range->end);

    int i = range->start;

    for (range->start; i < range->end; i++) {
        printf("thread %d is computing : %d\n", range->thread_id, i);
        range->tab[i] = get_time_of_flight_recursive(i, range->cache);

        sleep(1) ;
    }

    return NULL;
}

int main(int argc, char *argv[]) {

    if (argc == 2) {

        int input_size = atoi(argv[1]);
        printf("SIZE = %d\n", input_size);

        int *syracuse;
        syracuse = (int *) calloc((input_size + 1), sizeof(int)); // init a 0 ;

        // assert( syracuse != NULL );


        /* prepare cache  */
        cache_t cache;
        cache_init(&cache);


        pthread_t thread_1 ,thread_2, thread_3; // 1 to 10 , 11 to 20 , 21 to 30


        syracuse_args_t first = {1, &cache,syracuse,1,10};
        syracuse_args_t sec = {2,&cache,syracuse, 11, 20};
        syracuse_args_t third = { 3, &cache, syracuse,21, 30};

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
    } else {

        printf("Missing args format size syracuse\n");
        printf("Exemple : ./exo1 10\n");
        return EXIT_FAILURE;
    }


    return EXIT_SUCCESS;
}
