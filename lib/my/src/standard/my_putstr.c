/*
** EPITECH PROJECT, 2024
** libc
** File description:
** my_putstr.c
*/

#include "my.h"

/**
 * Outputs a string to the standard output.
 *
 * @param str Pointer to the null-terminated string to output.
 * @return Number of characters written on success, negative number on error.
 */
int my_putstr(char *str)
{
    return write(1, str, my_strlen(str));
}
