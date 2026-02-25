#ifndef ARENA_H
#define ARENA_H

#include <stdlib.h> // for size_t

typedef struct {
    char* start;
    int offset;
    int size;
} Arena;

// Initialize a stack-allocated arena
void arena_init(Arena* arena);

// Free internal memory (safe for stack-allocated arenas)
void arena_free_memory(Arena* arena);

// Reset offset to reuse memory
void arena_reset(Arena* arena);

// Mark/release support
int arena_mark(Arena* arena);
void arena_release(Arena* arena, int mark);

// Allocation with alignment
void* arena_alloc(Arena* arena, int size, int alignment);

// Macro for type-safe allocation
#define ARENA_PUSH(arena, type, n) \
    ((type*)arena_alloc(arena, (n) * sizeof(type), _Alignof(type)))

#endif // ARENA_H
