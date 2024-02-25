/*
** EPITECH PROJECT, 2024
** libc
** File description:
** my_strlen.c
*/

/**
 * Calculates the length of a string.
 *
 * @param str Pointer to the constant string whose length is to be calculated.
 * @return The length of the string, excluding the null-terminator.
 */
int my_strlen(char const *str)
{
    int i = 0;

    while (str[i])
        i++;
    return i;
}
