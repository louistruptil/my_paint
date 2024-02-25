/*
** EPITECH PROJECT, 2024
** libc
** File description:
** my_islower.c
*/

#include <stdbool.h>

/**
 * Determines if a character is a lowercase letter.
 *
 * @param character Character to test.
 * @return true if lowercase, false otherwise.
 */
bool my_islower(char character)
{
    return character >= 'a' && character <= 'z';
}
