/*
** EPITECH PROJECT, 2024
** Minishell1
** File description:
** my_free_array.c
*/

#include <stdlib.h>

void my_free_array(char **array)
{
    for (int i = 0; array[i]; i++)
        free(array[i]);
    free(array);
}
