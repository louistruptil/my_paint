/*
** EPITECH PROJECT, 2024
** libc
** File description:
** my_memcpy.c
*/

#include <stddef.h>

/**
 * Copies n bytes from memory area src to memory area dest.
 *
 * @param dest Destination memory area.
 * @param src Source memory area.
 * @param n Number of bytes to copy.
 * @return A pointer to dest.
 */
void *my_memcpy(void *dest, const void *src, size_t n)
{
    char *temp_dest = (char *)dest;
    const char *temp_src = (const char *)src;

    for (int i = 0; i < n; i++)
        temp_dest[i] = temp_src[i];
    return dest;
}
