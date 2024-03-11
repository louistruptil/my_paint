/*
** EPITECH PROJECT, 2024
** my_paint
** File description:
** my_paint.c
*/

#include "my_paint.h"

static int draw_cmd(my_paint_t *my_paint, sfEvent event)
{
    drawing_loop(my_paint, event);
}

static int ereased_cmd(my_paint_t *my_paint, sfEvent event)
{
    my_paint->tools.rgba[0] = 255;
    my_paint->tools.rgba[1] = 255;
    my_paint->tools.rgba[2] = 255;
    my_paint->tools.rgba[3] = 255;
    drawing_loop(my_paint, event);
}

void do_select_action(my_paint_t *my_paint, sfEvent event)
{
    if (!my_paint->can_draw)
        return;
    if (my_paint->tools.actual_tools == 0)
        draw_cmd(my_paint, event);
    if (my_paint->tools.actual_tools == 1)
        ereased_cmd(my_paint, event);
    if (my_paint->tools.actual_tools == 2)
        color_picker(my_paint, event);
    if (my_paint->tools.actual_tools == 3)
        color_bucket(my_paint, event);
}

void write_for_popup(my_paint_t *my_paint, sfEvent event)
{
    size_t len = 0;

    if (event.type == sfEvtTextEntered) {
        len = my_strlen(my_paint->window.popup_text_str);
        if (event.text.unicode == '\b' && len > 0)
            my_paint->window.popup_text_str[len - 1] = '\0';
        if (event.text.unicode >= 32 && event.text.unicode <= 126) {
            my_paint->window.popup_text_str[len] = event.text.unicode;
            my_paint->window.popup_text_str[len + 1] = '\0';
        }
        sfText_setString(my_paint->window.popup_text,
            my_paint->window.popup_text_str);
    }
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyReturn) {
        my_paint->tools.size = my_atoi(my_paint->window.popup_text_str);
        my_paint->window.popup_text_str[0] = '\0';
    }
}
