#include "syracuse.h"
#include <pthread.h>

// Fonction réalisant la suite de Syracuse à partir de l'entier n.
int get_time_of_flight(int n, int *tab, int table_size) {

    int k = 0 ;
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
