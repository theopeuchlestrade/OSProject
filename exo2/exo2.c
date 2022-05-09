
#include "exo2.h"
#include <stdio.h>
#include <stdlib.h>

int * Pascal(int numLigneFin){
    int * result = malloc(sizeof(int) * numLigneFin + 1);
    for(int numLigneActu = 0; numLigneActu <= numLigneFin; numLigneActu ++){
        int * ligneActu = calloc(sizeof(int), numLigneActu+1);
        ligneActu[0] = 1;
        
        //Calculating Pascal 
        int i = 1;
        
        switch(numLigneActu){
            case 0 : result[0] = 1;
                break;
            case 1 : result[0] = 1; result[1] = 1;
                break;
            case 2 : result[0] = 1; result[1] = 2; result[2] = 1;
                break;
            default:
                while(i <= numLigneActu){
                    ligneActu[i] = result[i-1] + result[i]; 
                    i++;
                }

                i = 0;
                while(i < numLigneActu){
                    result[i]= ligneActu[i];
                    i++;
                }
                result[numLigneActu] = 1;
                break;
        }

        free(ligneActu);
    }
    return result;
}



int main(int argc, char *argv[]) {
    printf("Exercice 2\n");

    int ligne = 0;
    printf("Choisir valeur ligne à calculer : ");
    scanf("%d", &ligne);

    int * result /*= calloc(sizeof(int), ligne + 1)*/;

    result = Pascal(ligne);
    for(int i = 0; i <= ligne; i++)
    {
        printf("Valeur numero %d de la ligne %d est : %d\n", i, ligne, result[i]);
    }
    
    free(result);
    return 0;
}