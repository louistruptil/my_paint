/*
** EPITECH PROJECT, 2024
** Project
** File description:
** my_putchar.c
*/

#include "my.h"

/**
 * @brief Outputs a character to the standard output.
 *
 * @param c Character to be written to stdout.
 * @return On success, returns the number of bytes written.
 * On error, returns a negative number.
 */
int my_putchar(char c)
{
    return (int)write(1, &c, 1);
}
