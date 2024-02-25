/*
** EPITECH PROJECT, 2024
** libc
** File description:
** my_isdigit.c
*/

#include <stdbool.h>

/**
 * Determines if a character is a decimal digit.
 *
 * @param character Character to test.
 * @return true if decimal digit, false otherwise.
 */
bool my_isdigit(char character)
{
    return character >= '0' && character <= '9';
}
