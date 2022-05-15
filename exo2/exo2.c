#include <assert.h>
#include <pthread.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "memory.h"

#ifndef NB_THREAD
# define NB_THREAD 10
#endif

t_memory *memory;

typedef struct
{
	int id;
	int line;
	int *previous_line;
	int *current_line;
	int start;
	int end;
} t_pascal_args;

#define CAN_COMPUTE(args, value) ((args)->start <= value && value <= (args)->end)

void*
pascal_runner(void *data)
{
	t_pascal_args *args = data;

	switch (args->line)
	{
		case 0:
			if (CAN_COMPUTE(args, 0))
				args->current_line[0] = 1;

			break;

		case 1:
			if (CAN_COMPUTE(args, 0))
				args->current_line[0] = 1;

			if (CAN_COMPUTE(args, 1))
				args->current_line[1] = 1;

			break;

		case 2:
			if (CAN_COMPUTE(args, 0))
				args->current_line[0] = 1;

			if (CAN_COMPUTE(args, 1))
				args->current_line[1] = 2;

			if (CAN_COMPUTE(args, 2))
				args->current_line[2] = 1;

			break;

		default:
			if (CAN_COMPUTE(args, 0))
				args->current_line[0] = 1;

			if (CAN_COMPUTE(args, args->line))
				args->current_line[args->line] = 1;

			for (int index = args->start; index < args->end; index++)
				args->current_line[index] = args->previous_line[index - 1] + args->previous_line[index];

			break;
	}

	return (NULL);
}

int*
calculLigneSuivante(int *result, int line)
{
	int thread_count = line;
	if (thread_count <= 0)
		thread_count = 1;
	if (thread_count > NB_THREAD)
		thread_count = NB_THREAD;

	pthread_t *threads = calloc(thread_count, sizeof(pthread_t));
	t_pascal_args *args = calloc(thread_count, sizeof(t_pascal_args));

	int iteration_count = 0;
	if (line % 2 == 1)
		iteration_count = (line + 1) / thread_count;
	else
		iteration_count = line / thread_count;

	t_block *current_line_block = block_alloc(memory, line + 1);

	for (int index = 0; index < thread_count; index++)
	{
		t_pascal_args *arg = &args[index];
		arg->id = index;
		arg->line = line;
		arg->previous_line = result;
		arg->current_line = current_line_block->start;
		arg->start = iteration_count * index;

		if (index == thread_count - 1)
			arg->end = line;
		else
			arg->end = iteration_count * (index + 1);
	}

	for (int index = 0; index < thread_count; index++)
		pthread_create(&threads[index], NULL, &pascal_runner, &args[index]);

	for (int index = 0; index < thread_count; index++)
		pthread_join(threads[index], NULL);

	memcpy(result, current_line_block->start, current_line_block->size);

	block_free(memory, current_line_block);

	free(threads);
	free(args);

	return (result);
}

int*
calculLigneN(int k)
{
	int *result = malloc(sizeof(int) * k + 1);
	if (!result)
	{
		perror("malloc");
		return (NULL);
	}

	for (int line = 0; line <= k; ++line)
		calculLigneSuivante(result, line);

	return (result);
}

int
main(int argc, char **argv)
{
	printf("NB_THREAD=%d\n", NB_THREAD);
	if (argc != 2)
	{
		dprintf(2, "usage: %s <n>\n", argv[0]);
		return (1);
	}

	int n = atoi(argv[1]);
	if (n < 0)
	{
		dprintf(2, "n: must not be negative");
		return (1);
	}
	printf("n=%d\n", n);

	memory = memory_create(sizeof(int), 4 * n);

//	for (int ligne = 0; ligne < n; ++ligne)
//	{
//		printf("ligne %d: ", ligne);
//		int *result = calculLigneSuivante(ligne);
//
//		for (int i = 0; i <= ligne; i++)
//		{
//			printf("[ %2d ]  ", result[i]);
//		}
//
//		free(result);
//		printf("\n");
//	}

	int *result = calculLigneN(n);
	for (int i = 0; i <= n; i++)
		printf("%2d ", result[i]);
	free(result);
	printf("\n");

	memory_destroy(memory);

	return (0);
}
