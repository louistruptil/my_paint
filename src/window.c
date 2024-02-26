/*
** EPITECH PROJECT, 2024
** my_paint
** File description:
** window.c
*/

#include "my_paint.h"

window_t create_window(int width, int height, char *title)
{
    window_t window;

    window.mode = (sfVideoMode){width, height, 32};
    window.window = sfRenderWindow_create(window.mode, title,
    sfDefaultStyle, NULL);
    window.view = sfView_createFromRect((sfFloatRect){0, 0, width, height});
    sfRenderWindow_setView(window.window, window.view);
    sfRenderWindow_setFramerateLimit(window.window, 60);
    return window;
}
