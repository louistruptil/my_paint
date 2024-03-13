/*
** EPITECH PROJECT, 2024
** my_paint
** File description:
** event.c
*/

#include "my_paint.h"

static void redo_act(my_paint_t *my_paint, button_t *button)
{
    my_putstr("Redo\n");
}

void btn_redo(my_paint_t *my_paint)
{
    my_paint->gui.button[13] = create_button((button_options_t) {
        {20, 725},
        {32, 32},
        sfColor_fromRGB(255, 255, 255),
        NULL,
        sfColor_fromRGB(255, 255, 255),
        "assets/redo.png"
    }, redo_act, NULL);
}