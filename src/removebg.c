/*
** EPITECH PROJECT, 2024
** my_paint
** File description:
** removebg.c
*/

#include "my_paint.h"

void remove_background(my_paint_t *my_paint, button_t *button)
{
    float threshold = 0.6;
    int index = 0;
    sfUint8 red = 0;
    sfUint8 green = 0;
    sfUint8 blue = 0;
    float lum = 0;

    for (int i = 0; i < 1920 * 1080; i++) {
        index = i * 4;
        red = my_paint->canva.canva_pixels[index];
        green = my_paint->canva.canva_pixels[index + 1];
        blue = my_paint->canva.canva_pixels[index + 2];
        lum = 0.299 * red + 0.587 * green + 0.114 * blue;
        if (lum > threshold * 255) {
            my_paint->canva.canva_pixels[index] = 0;
            my_paint->canva.canva_pixels[index + 1] = 0;
            my_paint->canva.canva_pixels[index + 2] = 0;
            my_paint->canva.canva_pixels[index + 3] = 0;
        }
    }
}

void btn_removebg(my_paint_t *my_paint)
{
    my_paint->gui.button[14] = create_button((button_options_t) {
        {11, 980},
        {50, 50},
        sfColor_fromRGB(85, 98, 120),
        "RM BG",
        sfColor_fromRGB(255, 255, 255),
    }, remove_background, NULL);
}
