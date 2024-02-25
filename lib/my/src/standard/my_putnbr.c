/*
** EPITECH PROJECT, 2024
** libc
** File description:
** my_putnbr.c
*/

#include "my.h"

/**
 * @brief Outputs an integer as a string to the standard output.
 *
 * @param number Integer to be converted and written to stdout.
 * @return On success, returns the number of characters written.
 * On error, returns a negative number.
 */
int my_putnbr(int number)
{
    char *num_str = my_itoa(number);

    return (int)write(1, num_str, my_strlen(num_str));
}
