/*
** EPITECH PROJECT, 2024
** my_paint
** File description:
** event.c
*/

#include "my_paint.h"

static void redo_act(my_paint_t *my_paint, button_t *button)
{
    printf("%p\n", my_paint->
    undoredo.canva_pixels[my_paint->undoredo.actual + 1]);
    if (my_paint->undoredo.actual < 9 && my_paint->
    undoredo.canva_pixels[my_paint->undoredo.actual + 1] != NULL) {
        printf("redo %d\n", my_paint->undoredo.actual);
        my_paint->undoredo.actual++;
        my_memcpy(my_paint->canva.canva_pixels,
        my_paint->undoredo.canva_pixels[my_paint->undoredo.actual],
        1920 * 1080 * 4);
    } else {
        my_putstr("There's nothing to redo\n");
    }
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
