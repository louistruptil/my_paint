/*
** EPITECH PROJECT, 2024
** my_paint
** File description:
** dropdown.c
*/

#include "my_paint.h"

drop_down_t *create_dropdown(button_options_t options)
{
    drop_down_t *dropdown = malloc(sizeof(drop_down_t));

    dropdown->button = create_button(options, NULL, NULL);
    return dropdown;
}

void add_item_to_dropdown(drop_down_t *dropdown, button_options_t options,
    void (*action)(my_paint_t *, button_t *), void (*hover)(button_t *))
{
    drop_down_item_t *new = malloc(sizeof(drop_down_item_t));
    drop_down_item_t *tmp = dropdown->items;

    if (tmp == NULL)
        options.pos.y += dropdown->button->options.size.y;
    else {
        while (tmp->next != NULL)
            tmp = tmp->next;
        options.pos.y = tmp->button->options.pos.y +
        tmp->button->options.size.y;
    }
    new->button = create_button(options, action, hover);
    new->next = NULL;
    if (tmp == NULL) {
        dropdown->items = new;
        return;
    }
    tmp->next = new;
}

void display_dropdown(sfRenderWindow *window, drop_down_t *dropdown)
{
    drop_down_t *tmp = dropdown;
    drop_down_item_t *tmp_items;

    display_button(window, tmp->button);
    if (!dropdown->is_open)
        return;
    tmp_items = tmp->items;
    while (tmp_items != NULL) {
        display_button(window, tmp_items->button);
        tmp_items = tmp_items->next;
    }
}
