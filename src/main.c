/*
** EPITECH PROJECT, 2024
** MyPaint
** File description:
** main.c
*/

#include "my_paint.h"

static void help(void)
{
    my_putstr("USAGE\n");
    my_putstr("    ./my_paint\n\n");
    my_putstr("DESCRIPTION\n");
    my_putstr("    A simple paint software\n");
}

int main(int argc, char **argv, char **env)
{
    if (argc == 2 && my_strcmp(argv[1], "-h") == 0) {
        help();
        return EXIT_SUCCESS;
    }
   for (int i = 0; env[i] != NULL; i++)
        if (my_strncmp(env[i], "DISPLAY", 7) == 0)
            return my_paint() ? EXIT_SUCCESS : EXIT_ERROR;    
    return EXIT_ERROR;
}
