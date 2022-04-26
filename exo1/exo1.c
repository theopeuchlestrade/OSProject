
#include "exo1.h"
#include <stdio.h>
#include <pthread.h>
#include "syracuse.h"


void *test(void *arg){

    syracuse_args_t range = *(syracuse_args_t*) arg;

    printf("Thread : %d will work on range %d, %d \n", (int) getpid(), range.start, range.end);
    while(1)
    return NULL;
}

int main()
{

    // Tableau qui stocke les valeurs de la fonction de syracuse
    // int *syracuse;
    // syracuse = (int *)malloc((SIZE + 1) * sizeof(int));
    // free(syracuse);

    pthread_t thread_1 ; // 1 to 10
    pthread_t thread_2 ; // 11 to 20
    pthread_t thread_3 ; // 21 to 30

    syracuse_args_t first = {
            .start = 1 ,
            .end = 10
    };

    syracuse_args_t sec = {
            .start = 11 ,
            .end = 20
    };

    syracuse_args_t third = {
            .start = 21 ,
            .end = 30
    };

    printf("pid of main is : %d\n", (int) getpid());


    pthread_create(&thread_1, NULL, &test, &first);
    pthread_create(&thread_2, NULL, &test, &sec);
    pthread_create(&thread_3, NULL, &test, &third);

    while(1);

    printf("Le thread initial/principale s'arrete. ");
    return EXIT_SUCCESS;
}
