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
    if (my_paint->gui.button[10] == NULL)
        return;
    for (int i = 0; i < BUTTON_COUNT; i++) {
        if (my_paint->gui.button[i]->is_clicked(my_paint->gui.button[i],
            &event.mouseButton))
            my_paint->gui.button[i]->action(my_paint, my_paint->gui.button[i]);
        if (my_paint->gui.button[i]->is_hover(my_paint->gui.button[i],
            &event.mouseMove)) {
        }
    }
    for (int i = 0; i < 9; i++) {
        if (my_paint->gui.color_palette[i]->is_clicked
            (my_paint->gui.color_palette[i], &event.mouseButton))
            my_paint->gui.color_palette[i]->
        action(my_paint, my_paint->gui.color_palette[i]);
        if (my_paint->gui.color_palette[i]->
            is_hover(my_paint->gui.color_palette[i], &event.mouseMove)) {
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
        my_paint->gui.dropdown[i]->button->is_hover
        (my_paint->gui.dropdown[i]->button, &event.mouseMove);
        if (!my_paint->gui.dropdown[i]->is_open)
            continue;
        tmp_items = my_paint->gui.dropdown[i]->items;
        dropdown_item_loop(event, my_paint, tmp_items);
    }
}

void zoom_canvas(my_paint_t *my_paint, button_t *button)
{
    my_paint->tools.canva_scale.x = 960;
    my_paint->tools.canva_scale.y = 540;
}

void dezoom_canvas(my_paint_t *my_paint, button_t *button)
{
    my_paint->tools.canva_scale.x = 1920;
    my_paint->tools.canva_scale.y = 1080;
}

static int popup_gestion(my_paint_t *my_paint, sfEvent event)
{
    if (my_paint->window.popup_size.display_popup == 1)
        write_for_popup(my_paint, event);
    if (my_paint->window.popup_open.display_popup == 1)
        write_for_popupopen(my_paint, event);
    if (my_paint->window.popup_save.display_popup == 1)
        write_for_popupsave(my_paint, event);
}

void event_loop(sfRenderWindow *window, sfEvent event, my_paint_t *my_paint)
{
    while (sfRenderWindow_pollEvent(window, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(window);
        if (event.type == sfEvtResized)
            sfRenderWindow_setView(window, sfView_createFromRect((sfFloatRect)
            {0, 0, event.size.width, event.size.height}));
        if (event.type == sfEvtKeyReleased && event.key.code == sfKeyP)
            zoom_canvas(my_paint, NULL);
        if (event.type == sfEvtKeyReleased && event.key.code == sfKeyO)
            dezoom_canvas(my_paint, NULL);
        if (event.type == sfEvtKeyReleased && event.key.code == sfKeyI)
            color_picker(my_paint, event);
        button_loop(event, my_paint);
        dropdown_loop(event, my_paint);
        do_select_action(my_paint, event);
        paste(my_paint, event);
        popup_gestion(my_paint, event);
    }
}
