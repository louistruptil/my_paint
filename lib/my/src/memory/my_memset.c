/*
** EPITECH PROJECT, 2024
** libc
** File description:
** my_memset.c
*/

#include "my.h"

/**
 * Initializes a block of memory to a specified value.
 *
 * @param ptr Pointer to the memory block.
 * @param value Byte value to set (as an int, converted to unsigned char).
 * @param num Number of bytes to set.
 * @return Pointer to the memory block (ptr).
 */
void *my_memset(void *ptr, int value, size_t num)
{
    unsigned char *p = ptr;

    for (; num; num--) {
        *p = (unsigned char)value;
        p++;
    }
    return ptr;
}
