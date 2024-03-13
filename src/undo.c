/*
** EPITECH PROJECT, 2024
** my_paint
** File description:
** event.c
*/

#include "my_paint.h"

static void undo_act(my_paint_t *my_paint, button_t *button)
{
    my_putstr("Undo\n");
}

void btn_undo(my_paint_t *my_paint)
{
    my_paint->gui.button[12] = create_button((button_options_t) {
        {20, 670},
        {32, 32},
        sfColor_fromRGB(255, 255, 255),
        NULL,
        sfColor_fromRGB(255, 255, 255),
        "assets/undo.png"
    }, undo_act, NULL);
}