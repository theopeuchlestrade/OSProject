#include <pthread.h>
#include "syracuse.h"

// Fonction réalisant la suite de Syracuse à partir de l'entier n.

void display_syracuse(int *tab){
    printf("[ syracuse ] \n") ;
    for (int i = 0; i < SIZE; ++i) {
        printf("[ %5d | %5d ] \n", i, tab[i]) ;
    }
}


int get_time_of_flight_recursive(int n, cache_t *cache) {

    if (n == 1) {
        return 0;

    } else if (n % 2 == 0) {
        return get_time_of_flight_recursive(n / 2, cache) + 1;
    } else {
        return get_time_of_flight_recursive(3 * n + 1, cache) + 1;
    }
}

int get_time_of_flight(int n, int *tab, int table_size) {

    int k = 0;
    int i = 1;
    tab[0] = table_size;
    printf("%d =>  %d\n", 0, tab[0]);

    while (n > 1) {
        if (n % 2 == 0) {
            n /= 2;
            tab[i] = n;
            printf("%d =>  %d\n", i, n);

        } else {
            n = 3 * n + 1;
            tab[i] = n;
            printf("%d =>  %d\n", i, n);
        }
        i++;
        k++;
    }

    return k;
}
