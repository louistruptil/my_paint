/*
** EPITECH PROJECT, 2024
** libc
** File description:
** my_isupper.c
*/

#include <stdbool.h>

/**
 * Determines if a character is an uppercase letter.
 *
 * @param character Character to test.
 * @return true if uppercase, false otherwise.
 */
bool my_isupper(char character)
{
    return character >= 'A' && character <= 'Z';
}
