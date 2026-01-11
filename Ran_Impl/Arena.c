#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

typedef struct{
	size_t capacity;
	size_t size;
	uint8_t *data;
} Arena;

Arena initialize(size_t capacity){ //initializing the arena
	void *data = malloc(sizeof(uint8_t)*capacity);
	Arena arena = {
		.capacity = capacity,
		.size = 0,
		.data = data,
	};
	return arena;
}

void* arena_alloc(Arena* arena ,size_t size){ //allocating space in the arena
	assert(arena->size + size <= arena->capacity);
	uint8_t *data = &arena->data[arena->size];
	arena->size += size;
	return data;
}

void* arena_reset(Arena* arena){
	arena->size = 0;
}

void* arena_free(Arena* arena){
	arena->size = 0;
	arena->capacity = 0;
	free(arena->data);
}

void* arena_print(Arena* arena){
	printf("arena size: %zu\n",arena->size);
	printf("arena capacity: %zu\n",arena->capacity);
	printf("data ptr: %d\n",arena->data);
}

int main(){
	Arena arena = initialize(1024);
	void* ptr = arena_alloc(&arena, 255);
	void* ptr2 = arena_alloc(&arena, 700);
	printf("ptr:%d, ptr2:%d\n", ptr, ptr2);
	arena_print(&arena);
	arena_reset(&arena);
	arena_print(&arena);
	arena_free(&arena);
	arena_print(&arena);
	return 0;
}
