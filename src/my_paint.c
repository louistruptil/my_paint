/*
** EPITECH PROJECT, 2024
** my_paint
** File description:
** my_paint.c
*/

#include "my_paint.h"

void destroy(my_paint_t *my_paint)
{
    for (int i = 0; i < BUTTON_COUNT; i++)
        destroy_button(my_paint->gui.button[i]);
    sfRenderWindow_destroy(my_paint->window.window);
    free(my_paint);
}

void display(my_paint_t *my_paint)
{
    sfRenderWindow_clear(my_paint->window.window, sfWhite);
    for (int i = 0; i < BUTTON_COUNT; i++) {
        display_button(my_paint->window.window, my_paint->gui.button[i]);
    }
}

void print_action(my_paint_t *my_paint)
{
    my_putstr("Button clicked\n");
}

bool my_paint(void)
{
    my_paint_t *my_paint = malloc(sizeof(my_paint_t));

    if (!my_paint)
        return false;
    my_paint->window = create_window(WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
    my_paint->gui.button[0] = create_button((button_options_t){
        {100, 100},
        {750, 400},
        sfRed,
        "Hello"
    }, print_action);
    while (sfRenderWindow_isOpen(my_paint->window.window)) {
        event_loop(my_paint->window.window, my_paint->window.event, my_paint);
        display(my_paint);
        sfRenderWindow_display(my_paint->window.window);
    }
    destroy(my_paint);
    return true;
}
