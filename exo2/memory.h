#ifndef MEMORY_H
# define MEMORY_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <semaphore.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef enum
{
	FREE = 1,
	USED
} e_block_flag;

typedef struct
{
		void *start;
		int size; // in byte
		e_block_flag flag;
} t_block;

typedef struct
{
		int size; // sizeof
		int count;
		void *blocks;
		sem_t *lock;
} t_memory;

#define MEMORY_SIZE_BYTE(ptr) ((ptr)->count * (sizeof(t_block) + (ptr)->size))
#define MEMORY_LOCK(ptr) if (sem_wait((ptr)->lock) == -1) { perror("sem_wait"); };
#define MEMORY_UNLOCK(ptr) if (sem_post((ptr)->lock) == -1) { perror("sem_post"); };
#define BLOCK_NEXT(ptr) ((ptr)->start + (ptr)->size)
#define BLOCK_IS_LAST(memory_ptr, block_ptr) ((void*)(block_ptr) >= (void*)(((char*)(memory_ptr)->blocks) + MEMORY_SIZE_BYTE(memory_ptr)))

#ifdef DEBUG
# define MEMORY_DEBUG(format, ...) printf(format, __VA_ARGS__)
#else
# define MEMORY_DEBUG(format, ...) (void)0
#endif

t_memory*
memory_create(int size, int count);

t_block*
block_alloc(t_memory *memory, int size_to_allocate);

void
block_free(t_memory *memory, t_block *block_to_free);

void
memory_destroy(t_memory *memory);

void
memory_print(t_memory *memory);

#endif
