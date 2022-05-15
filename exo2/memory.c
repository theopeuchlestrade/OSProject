#include "memory.h"

t_memory*
memory_create(int size, int count)
{
	t_memory *memory = malloc(sizeof(t_memory));
	if (!memory)
	{
		perror("malloc");
		return (NULL);
	}

	char buff[255] = { 0 };
	sprintf(buff, "%p", memory);

	sem_unlink(buff);

	errno = 0;
	memory->lock = sem_open(buff, O_RDWR | O_CREAT | O_EXCL, 0777, 1);
	if (memory->lock == SEM_FAILED)
	{
		perror("sem_open");
		free(memory);
		return (NULL);
	}

	memory->size = size;
	memory->count = count;
	memory->blocks = malloc(MEMORY_SIZE_BYTE(memory));

	t_block *first = memory->blocks;
	first->start = ((char*)memory->blocks) + sizeof(t_block);
	first->size = MEMORY_SIZE_BYTE(memory) - sizeof(t_block);
	first->flag = FREE;

	return (memory);
}

t_block*
block_alloc(t_memory *memory, int size_to_allocate)
{
	MEMORY_LOCK(memory);
	MEMORY_DEBUG("block_alloc: memory=%p size_to_allocate=%d\n", memory, size_to_allocate);

	t_block *block = memory->blocks;

	int size_in_byte = memory->size * size_to_allocate;

	while (!BLOCK_IS_LAST(memory, block))
	{
		if (block->flag == FREE && block->size >= size_in_byte)
		{
			block->flag = USED;

			int old_size = block->size;
			block->size = size_in_byte;

			t_block *next_block = (void*)((char*)block->start + block->size);
			next_block->flag = FREE;
			next_block->start = (char*)next_block + sizeof(t_block);
			next_block->size = old_size - size_in_byte - sizeof(t_block);

			MEMORY_UNLOCK(memory);
			return (block);
		}

		block = BLOCK_NEXT(block);
	}

	MEMORY_UNLOCK(memory);
	return (NULL);
}

void
block_free(t_memory *memory, t_block *block_to_free)
{
	MEMORY_LOCK(memory);
	MEMORY_DEBUG("block_free: memory=%p block_to_free=%p\n", memory, block_to_free);

	t_block *block = memory->blocks;
	t_block *previous = NULL;

	while (!BLOCK_IS_LAST(memory, block))
	{
		t_block *next = BLOCK_NEXT(block);
		if (BLOCK_IS_LAST(memory, block))
			next = NULL;

		if (block == block_to_free)
		{
			block->flag = FREE;

			if (previous && previous->flag == FREE)
			{
				previous->size += block->size + sizeof(t_block);
				block = previous;
			}

			if (next && next->flag == FREE)
			{
				block->size += next->size + sizeof(t_block);
			}

			memset(block->start, 0, block->size);

			MEMORY_UNLOCK(memory);
			return;
		}

		previous = block;
		block = BLOCK_NEXT(block);
	}

	MEMORY_UNLOCK(memory);

	dprintf(2, "block_free: block %p not found\n", block_to_free);
	abort();
}

void
memory_destroy(t_memory *memory)
{
	sem_destroy(memory->lock);
	free(memory->blocks);
	free(memory);
}

void
memory_print(t_memory *memory)
{
	static const char *FLAGS[] = { "none", "free", "used" };

	MEMORY_LOCK(memory);

	t_block *block = memory->blocks;

	while (!BLOCK_IS_LAST(memory, block))
	{
		printf("block=%p start=%p flag=%s size=%d\n", block, block->start, FLAGS[block->flag], block->size);

		block = BLOCK_NEXT(block);
	}

	MEMORY_UNLOCK(memory);
}
