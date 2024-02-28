/*
** EPITECH PROJECT, 2024
** my_paint
** File description:
** event.c
*/

#include "my_paint.h"

static void button_loop(sfEvent event, const my_paint_t *my_paint)
{
    for (int i = 0; i < BUTTON_COUNT; i++) {
        if (my_paint->gui.button[i]->is_clicked(my_paint->gui.button[i],
        &event.mouseButton)) {
            my_paint->gui.button[i]->action(my_paint);
        }
        if (my_paint->gui.button[i]->is_hover(my_paint->gui.button[i],
        &event.mouseMove)) {
            my_putstr("Hover\n");
        }
    }
}

void update_canvas_scale(my_paint_t *my_paint) {
    sfVector2u windowSize = sfRenderWindow_getSize(my_paint->window.window);
    sfVector2u textureSize = sfTexture_getSize(my_paint->canva.canva_texture);
    float scaleX = (float)windowSize.x / textureSize.x;
    float scaleY = (float)windowSize.y / textureSize.y;
    sfVector2f textureCenter = {(float)textureSize.x / 2, (float)textureSize.y / 2}; // Calculate texture center
    sfSprite_setOrigin(my_paint->canva.canva_sprite, textureCenter); // Set origin to texture center
    sfSprite_setScale(my_paint->canva.canva_sprite, (sfVector2f){scaleX, scaleY});
    
    // Update canvas position
    sfVector2f newPosition = {(float)windowSize.x / 2, (float)windowSize.y / 2}; // Center canvas in window
    sfSprite_setPosition(my_paint->canva.canva_sprite, newPosition);
}

static void drawing_loop(my_paint_t *my_paint, sfEvent event)
{
    if (event.type == sfEvtMouseButtonPressed)
        my_paint->canva.canva_drawing = sfTrue;
    if (event.type == sfEvtMouseButtonReleased)
        my_paint->canva.canva_drawing = sfFalse;
    if (my_paint->canva.canva_drawing) {
        sfVector2i mousePos = sfMouse_getPositionRenderWindow(my_paint->window.window);
        sfVector2f scale = sfSprite_getScale(my_paint->canva.canva_sprite);
            int x = mousePos.x / scale.x;
            int y = mousePos.y / scale.y;
            int size = 10;
            for (int dy = -size/2; dy < size/2; dy++) {
                for (int dx = -size/2; dx < size/2; dx++) {
                    if (x+dx >= 0 && x+dx < 1920 && y+dy >= 0 && y+dy < 1080) {
                        int index = 4 * ((y+dy) * 1920 + (x+dx));
                        my_paint->canva.canva_pixels[index] = 0;
                        my_paint->canva.canva_pixels[index + 1] = 0;
                        my_paint->canva.canva_pixels[index + 2] = 0;
                        my_paint->canva.canva_pixels[index + 3] = 255;
                    }
                }
            }
            sfTexture_updateFromPixels(my_paint->canva.canva_texture, my_paint->canva.canva_pixels, 1920, 1080, 0, 0);
        }
}

void event_loop(sfRenderWindow *window, sfEvent event, my_paint_t *my_paint)
{
    while (sfRenderWindow_pollEvent(window, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(window);
        if (event.type == sfEvtResized)
            sfRenderWindow_setView(window, sfView_createFromRect((sfFloatRect)
            {0, 0, event.size.width, event.size.height}));
            update_canvas_scale(my_paint);
        button_loop(event, my_paint);
        drawing_loop(my_paint, event);
    }
}
