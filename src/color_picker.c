/*
** EPITECH PROJECT, 2024
** my_paint
** File description:
** event.c
*/

#include <stdio.h>

#include "my_paint.h"
int color_picker(my_paint_t *my_paint, sfEvent event)
{
    if (event.type == sfEvtMouseButtonPressed && event.mouseButton.button == sfMouseLeft) {
        sfVector2i mousePos = sfMouse_getPositionRenderWindow(my_paint->window.window);
        sfVector2u windowSize = sfRenderWindow_getSize(my_paint->window.window);
        sfVector2f scale = {1920.0f / windowSize.x, 1080.0f / windowSize.y};
        int mouseX = mousePos.x * scale.x;
        int mouseY = mousePos.y * scale.y;

        if (mouseX >= 0 && mouseX < 1920 && mouseY >= 0 && mouseY < 1080) {
            int pixel_index = (mouseY * 1920 + mouseX) * 4;
            my_paint->tools.rgba[0] = my_paint->canva.canva_pixels[pixel_index];
            my_paint->tools.rgba[1] = my_paint->canva.canva_pixels[pixel_index + 1];
            my_paint->tools.rgba[2] = my_paint->canva.canva_pixels[pixel_index + 2];
            my_paint->tools.rgba[3] = my_paint->canva.canva_pixels[pixel_index + 3];
        }
    }
}