/*
** EPITECH PROJECT, 2024
** libc
** File description:
** my_isspace.c
*/

#include <stdbool.h>

/**
 * Determines if a character is a space.
 *
 * @param character Character to test.
 * @return true if space, false otherwise.
 */
bool my_isspace(char character)
{
    if (character == ' ')
        return true;
    return false;
}
