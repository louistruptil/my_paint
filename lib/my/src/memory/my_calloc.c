/*
** EPITECH PROJECT, 2024
** libc
** File description:
** my_calloc.c
*/

#include "my.h"

/**
 * Allocates and zeros memory for an array.
 *
 * @param num_elements Number of elements.
 * @param element_size Element size in bytes.
 * @return Pointer to zero-initialized memory, or NULL if allocation fails.
 */
void *my_calloc(size_t num_elements, size_t element_size)
{
    size_t size = num_elements * element_size;
    void *ptr = malloc(size);

    if (ptr != NULL)
        my_memset(ptr, 0, size);
    return ptr;
}
