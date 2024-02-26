/*
** EPITECH PROJECT, 2024
** my_paint
** File description:
** event.c
*/

#include "my_paint.h"

static void button_loop(sfEvent event, const my_paint_t *my_paint)
{
    for (int i = 0; i < BUTTON_COUNT; i++) {
        if (my_paint->gui.button[i]->is_clicked(my_paint->gui.button[i],
        &event.mouseButton)) {
            my_paint->gui.button[i]->action(my_paint);
        }
        if (my_paint->gui.button[i]->is_hover(my_paint->gui.button[i],
        &event.mouseMove)) {
            my_putstr("Hover\n");
        }
    }
}

void event_loop(sfRenderWindow *window, sfEvent event, my_paint_t *my_paint)
{
    while (sfRenderWindow_pollEvent(window, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(window);
        if (event.type == sfEvtResized)
            sfRenderWindow_setView(window, sfView_createFromRect((sfFloatRect)
            {0, 0, event.size.width, event.size.height}));
        button_loop(event, my_paint);
    }
}
