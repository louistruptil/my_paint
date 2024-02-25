/*
** EPITECH PROJECT, 2024
** libc
** File description:
** my_realloc.c
*/

#include "my.h"

/**
 * Resizes a previously allocated memory block.
 *
 * @param ptr Pointer to the allocated memory.
 * @param new_size New size in bytes.
 * @return Pointer to the resized memory, or NULL if resizing fails.
 */
void *my_realloc(void *ptr, size_t new_size)
{
    void *new_ptr;

    if (new_size == 0) {
        free(ptr);
        return NULL;
    }
    if (!ptr)
        return malloc(new_size);
    new_ptr = malloc(new_size);
    if (new_ptr) {
        my_memcpy(new_ptr, ptr, new_size);
        free(ptr);
    }
    return new_ptr;
}
