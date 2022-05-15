#include <assert.h>
#include <pthread.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define CAN_COMPUTE(args, value) ((args)->start <= value && value <= (args)->end)

#ifndef NB_THREAD
# define NB_THREAD 10
#endif

typedef struct
{
	int id;
	int line;
	int *previous_line;
	int *current_line;
	int start;
	int end;
} t_pascal_args;


void*
pascal_runner(void *data);

int*
calculLigneSuivante(int *result, int line);

int*
calculLigneN(int k);