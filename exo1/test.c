
#include <stdio.h>
#include "syracuse.h"
/*
int main(int argc, char *argv[]) {


    cache_t cache ;

    cache_init(&cache);


    printf("%d\n", cache_get(&cache, 4));

    cache_set(&cache,4,9);

    printf("%d\n", cache_get(&cache, 4));

    cache_del(&cache,4);
    cache_del(&cache,4);

    printf("%d\n", cache_get(&cache, 4));

    cache_destroy(&cache);

    return 0;
}

 */
/*
int main(int argc, char *argv[]) {

    printf("%d\n" , argc);
    if (argc == 3 ) {

        int input_size  =  atoi(argv[1]);
        int input_number = atoi(argv[2]);

        int *syracuse = (int *)malloc((input_size + 1) * sizeof(int));

        funSyracuse(input_number, syracuse, input_size) ;

        for (int i = 0; i < 10 ; ++i) {
            printf("index = %d => %d\n", i, syracuse[i]);
        }

        free(syracuse);
    }

    return 0;
}
 */