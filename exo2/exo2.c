
#include "exo2.h"
#include <stdio.h>
#include <stdlib.h>


void compute_current_line(const int line_number,int *line_prec){

    int *new_line = calloc(line_number + 1, sizeof(int));

    new_line[0] = 1;

    for (int index = 1; index < line_number; index++) {
        new_line[index] = line_prec[index-1] + line_prec[index];
    }
    new_line[line_number] = 1;

    for (int index = 1; index < line_number; index++) {
        line_prec[index] = new_line[index];
    }
    free(new_line);

}

void Pascal(int *result, int numLigneFin){


    for(int numLigneActu = 0; numLigneActu <= numLigneFin; numLigneActu ++){

        //Calculating Pascal 

        switch(numLigneActu){
            case 0 : result[0] = 1;
                break;
            case 1 : result[0] = 1; result[1] = 1;
                break;
            case 2 : result[0] = 1; result[1] = 2; result[2] = 1;
                break;
            default:
                compute_current_line(numLigneActu, result);
                break;
        }
    }
}



int main(int argc, char *argv[]) {
    printf("Exercice 2\n");

    int ligne = 0;
    printf("Choisir valeur ligne à calculer : ");
    scanf("%d", &ligne);

    int *result = calloc((ligne + 1), sizeof(int));

    Pascal(result, ligne);

    for(int i = 0; i <= ligne; i++)
    {
        printf("Valeur numero %d de la ligne %d est : %d\n", i, ligne, result[i]);
    }
    
    free(result);
    return 0;
}