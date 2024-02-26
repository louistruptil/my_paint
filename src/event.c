/*
** EPITECH PROJECT, 2024
** my_paint
** File description:
** event.c
*/

#include "my_paint.h"

void event_loop(sfRenderWindow *window, sfEvent event, my_paint_t *my_paint)
{
    while (sfRenderWindow_pollEvent(window, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(window);
        if (event.type == sfEvtResized)
            sfRenderWindow_setView(window, sfView_createFromRect((sfFloatRect)
            {0, 0, event.size.width, event.size.height}));
    }
}
