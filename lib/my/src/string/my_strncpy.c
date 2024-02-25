/*
** EPITECH PROJECT, 2024
** libc
** File description:
** my_strncpy.c
*/

#include "my.h"

/**
 * Copies up to n characters from a source string to a destination string.
 *
 * @param dest Pointer to the destination string,
 *      which should be large enough to store the copied characters.
 * @param src Pointer to the constant source string to be copied.
 * @param n The number of characters to copy from the source string.
 * @return Pointer to the destination string after copying.
 */
char *my_strncpy(char *dest, char const *src, int n)
{
    int i;

    for (i = 0; i < n; i++)
        dest[i] = src[i];
    if (n > my_strlen(src)) {
        dest[i] = '\0';
        return dest;
    }
    return dest;
}
