/*
** EPITECH PROJECT, 2024
** my_paint
** File description:
** zoom.c
*/

#include "my_paint.h"

void btn_zoom(my_paint_t *my_paint)
{
    my_paint->gui.button[4] = create_button((button_options_t) {
        {20, 285},
        {32, 32},
        sfColor_fromRGB(255, 255, 255),
        NULL,
        sfColor_fromRGB(255, 255, 255),
        "assets/zoom.png"
    }, zoom_canvas, NULL);
}

void btn_dezoom(my_paint_t *my_paint)
{
    my_paint->gui.button[5] = create_button((button_options_t) {
        {20, 340},
        {32, 32},
        sfColor_fromRGB(255, 255, 255),
        NULL,
        sfColor_fromRGB(255, 255, 255),
        "assets/dezoomer.png"
    }, dezoom_canvas, NULL);
}
