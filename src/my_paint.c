/*
** EPITECH PROJECT, 2024
** my_paint
** File description:
** my_paint.c
*/

#include "my_paint.h"

void destroy(my_paint_t *my_paint)
{
    sfRenderWindow_destroy(my_paint->window.window);
    free(my_paint);
}

void display(my_paint_t *my_paint)
{
    sfRenderWindow_clear(my_paint->window.window, sfWhite);
}

bool my_paint(void)
{
    my_paint_t *my_paint = malloc(sizeof(my_paint_t));

    if (!my_paint)
        return false;
    my_paint->window = create_window(WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
    while (sfRenderWindow_isOpen(my_paint->window.window)) {
        event_loop(my_paint->window.window, my_paint->window.event, my_paint);
        display(my_paint);
        sfRenderWindow_display(my_paint->window.window);
    }
    destroy(my_paint);
    return true;
}
