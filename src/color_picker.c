/*
** EPITECH PROJECT, 2024
** my_paint
** File description:
** event.c
*/

#include "my_paint.h"

int color_picker(my_paint_t *my_paint, sfEvent event)
{
    sfVector2i mouse_pos =
        sfMouse_getPositionRenderWindow(my_paint->window.window);
    sfVector2u winodw_pos = sfRenderWindow_getSize(my_paint->window.window);
    sfVector2f scale = {1920.0f / winodw_pos.x, 1080.0f / winodw_pos.y};
    int mouseX = mouse_pos.x * scale.x;
    int mouseY = mouse_pos.y * scale.y;
    int pixel = (mouseY * 1920 + mouseX) * 4;

    if (event.type == sfEvtMouseButtonPressed &&
        event.mouseButton.button == sfMouseLeft) {
        if (mouseX >= 0 && mouseX < 1920 && mouseY >= 0 && mouseY < 1080) {
            my_paint->tools.rgba[0] = my_paint->canva.canva_pixels[pixel];
            my_paint->tools.rgba[1] = my_paint->canva.canva_pixels[pixel + 1];
            my_paint->tools.rgba[2] = my_paint->canva.canva_pixels[pixel + 2];
            my_paint->tools.rgba[3] = my_paint->canva.canva_pixels[pixel + 3];
        }
    }
}
