/*
** EPITECH PROJECT, 2024
** my_paint
** File description:
** event.c
*/

#include <stdio.h>

#include "my_paint.h"

static void button_loop(sfEvent event, my_paint_t *my_paint)
{
    for (int i = 0; i < BUTTON_COUNT; i++) {
        if (my_paint->gui.button[i]->is_clicked(my_paint->gui.button[i],
            &event.mouseButton)) {
            my_paint->gui.button[i]->action(my_paint, my_paint->gui.button[i]);
        }
        if (my_paint->gui.button[i]->is_hover(my_paint->gui.button[i],
            &event.mouseMove)) {
        }
    }
}

static void dropdown_item_loop(sfEvent event, my_paint_t *my_paint,
    drop_down_item_t *tmp_items)
{
    while (tmp_items != NULL) {
        if (tmp_items->button->is_clicked
        (tmp_items->button, &event.mouseButton)) {
            tmp_items->button->action(my_paint, tmp_items->button);
        }
        if (tmp_items->button->is_hover(tmp_items->button, &event.mouseMove)) {
            tmp_items->button->hover(tmp_items->button);
        }
        tmp_items = tmp_items->next;
    }
}

static void dropdown_loop(sfEvent event, my_paint_t *my_paint)
{
    sfFloatRect rect;
    sfVector2i mouse = sfMouse_getPositionRenderWindow(WINDOW);
    sfBool is_hover;
    drop_down_item_t *tmp_items;

    for (int i = 0; i < DROPDOWN_COUNT; i++) {
        rect = sfRectangleShape_getGlobalBounds
        (my_paint->gui.dropdown[i]->button->rect);
        is_hover = sfFloatRect_contains(&rect, mouse.x, mouse.y);
        if (is_hover && event.type == sfEvtMouseButtonReleased) {
            my_paint->gui.dropdown[i]->is_open =
            !my_paint->gui.dropdown[i]->is_open;
        }
        if (!my_paint->gui.dropdown[i]->is_open)
            continue;
        tmp_items = my_paint->gui.dropdown[i]->items;
        dropdown_item_loop(event, my_paint, tmp_items);
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
        if (event.type == sfEvtKeyReleased && event.key.code == sfKeyB) {
            printf("mouse pos: %d %d\n", sfMouse_getPositionRenderWindow(WINDOW).x, sfMouse_getPositionRenderWindow(WINDOW).y);
            flood_fill(my_paint, sfMouse_getPositionRenderWindow(WINDOW).x, sfMouse_getPositionRenderWindow(WINDOW).y, sfBlue);
        }
        if (event.type == sfEvtKeyReleased && event.key.code == sfKeyL)
            color_picker(my_paint, event);
        button_loop(event, my_paint);
        dropdown_loop(event, my_paint);
        do_select_action(my_paint, event);
    }
}
