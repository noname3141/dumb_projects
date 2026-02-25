/*
Absolutely! Implementing an **arena allocator** in C is a fantastic systems programming exercise. I’ll make a clear, step-by-step **to-do list** for you. Each step builds on the previous one, so you can follow it sequentially.

---

# To-Do List: Step-by-Step Arena Allocator in C

### **1. Define Your Arena Structure**

* Decide on a **fixed block of memory** or dynamically allocated memory for your arena.
* Typical fields:

  * Pointer to the start of memory (`char* start`)
  * Current offset (`size_t offset`)
  * Total size (`size_t size`)

```c
typedef struct Arena {
    char* start;
    size_t size;
    size_t offset;
} Arena;
```

---

### **2. Initialize the Arena**

* Write a function to allocate memory for the arena and set `offset = 0`.
* Use `malloc` or `aligned_alloc` for the underlying memory.

```c
Arena* arena_init(size_t size);
```

---

### **3. Implement Allocation Function**

* Function to allocate memory from the arena:

  * Check if there’s enough space (`offset + requested_size <= size`)
  * Return pointer at `start + offset`
  * Increment `offset` by `requested_size`

```c
void* arena_alloc(Arena* arena, size_t size);
```

---

### **4. (Optional) Alignment Support**

* Ensure allocations are aligned (e.g., 8-byte alignment).
* Calculate padding for alignment and add it to `offset`.

---

### **5. Implement Reset / Free Functions**

* `arena_reset(Arena* arena)` – resets `offset = 0` to reuse memory.
* `arena_free(Arena* arena)` – frees underlying memory when done.

---

### **6. (Optional) Add Mark and Release**

* Implement `arena_mark(Arena*)` to save the current `offset`.
* Implement `arena_release(Arena*, mark)` to rollback to that point.
* Useful for temporary allocations that you want to free all at once.

---

### **7. Test Basic Allocations**

* Allocate several objects and check:

  * Addresses are contiguous
  * Allocations respect alignment
  * Reset works as expected

---

### **8. (Optional) Growable Arena**

* If you want dynamic resizing:

  * Allocate a larger block
  * Copy existing data
  * Update `start` and `size`

---

### **9. Use Macros for Convenience**

* Define macros like `ARENA_PUSH(arena, type)` to simplify allocation syntax.

```c
#define ARENA_PUSH(arena, type) (type*)arena_alloc(arena, sizeof(type))
```

---

### **10. Benchmark / Validate**

* Test with real workloads (e.g., parsing, temporary buffers).
* Check for memory leaks with tools like `valgrind`.

---

If you want, I can also write a **full minimal C implementation** of this arena allocator with all the steps above in **under 100 lines**, so you can see it working end-to-end.

Do you want me to do that?

*/

#include <stdio.h>
#include "Arena.h"

#define SIZE 200

void arena_init(Arena* arena){
    arena->start = malloc(SIZE*sizeof(char));
    arena->offset = 0;
    arena->size = SIZE;
}

void arena_grow(Arena* arena){
    char* ptr = realloc(arena->start, 2*arena->size*sizeof(char)); //reallocing twice the size of the original size
    if(!ptr) return; //if realloc fails
    arena->size *= 2;
    arena->start = ptr;
}

void arena_free(Arena* arena){
    if(arena == NULL) return;
    if(arena->start != NULL){
        free(arena->start);
        arena->start = NULL;
    }
}

void arena_reset(Arena* arena){
    arena->offset = 0;
}

int arena_offset(Arena* arena, int alignment){
    int misalign = arena->offset % alignment;
    if(misalign == 0) return arena->offset;
    return arena->offset + (alignment - misalign);
}

void* arena_alloc(Arena* arena, int size, int alignment){
    int arenaoffset = arena_offset(arena, alignment);
    while(arenaoffset + size > arena->size){
        arena_grow(arena);
        if(arena->start == NULL) return NULL;
    }
    char* buf = arena->start + arenaoffset;
    arena->offset = arenaoffset + size;
    return buf;
}

int arena_mark(Arena* arena){
    int mark = arena->offset;
    return mark;
}

void arena_release(Arena* arena,int mark){
    arena->offset = mark;
}

int main(){
    Arena arena;
    arena_init(&arena);
    int* a = ARENA_PUSH(&arena, int, 1);       // aligned to 4 bytes
    double* d = ARENA_PUSH(&arena, double, 1); // aligned to 8 bytes
    //using all the implemented functions to simulate an arena
    *a = 10;
    *d = 20;
    int c = *a + *d;
    printf("%d + %f = %d\n", *a, *d, c);
    arena_reset(&arena);
    arena_free(&arena);
    return c;
}
