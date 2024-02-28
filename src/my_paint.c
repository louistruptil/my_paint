/*
** EPITECH PROJECT, 2024
** my_paint
** File description:
** my_paint.c
*/

#include "my_paint.h"

void destroy(my_paint_t *my_paint)
{
    for (int i = 0; i < BUTTON_COUNT; i++)
        destroy_button(my_paint->gui.button[i]);
    sfRenderWindow_destroy(my_paint->window.window);
    free(my_paint);
}

void display_canva(my_paint_t *my_paint)
{
    sfTexture_updateFromPixels(my_paint->canva.canva_texture, my_paint->canva.canva_pixels, 1920, 1080, 0, 0);
    sfRenderWindow_drawSprite(my_paint->window.window, my_paint->canva.canva_sprite, NULL);
}

void display(my_paint_t *my_paint)
{
    sfRenderWindow_clear(my_paint->window.window, sfWhite);
    display_canva(my_paint);
    for (int i = 0; i < BUTTON_COUNT; i++) {
        display_button(my_paint->window.window, my_paint->gui.button[i]);
    }
    sfRenderWindow_display(my_paint->window.window);
}

void print_action(my_paint_t *my_paint)
{
    my_putstr("Button clicked\n");
}

static void init_canva(my_paint_t *my_paint)
{
    my_paint->canva.canva_pixels = malloc(1920 * 1080 * 4);
    for (int i = 0; i < 1920 * 1080 * 4; i += 4) {
        my_paint->canva.canva_pixels[i] = 255;
        my_paint->canva.canva_pixels[i + 1] = 255;
        my_paint->canva.canva_pixels[i + 2] = 255;
        my_paint->canva.canva_pixels[i + 3] = 255;
    }
    my_paint->canva.canva_texture = sfTexture_create(1920, 1080);
    my_paint->canva.canva_sprite = sfSprite_create();
    sfVector2u windowSize = sfRenderWindow_getSize(my_paint->window.window);
    sfVector2u textureSize = sfTexture_getSize(my_paint->canva.canva_texture);
    float scaleX = (float)windowSize.x / textureSize.x;
    float scaleY = (float)windowSize.y / textureSize.y;
    sfSprite_setScale(my_paint->canva.canva_sprite, (sfVector2f){scaleX, scaleY});
    sfSprite_setTexture(my_paint->canva.canva_sprite, my_paint->canva.canva_texture, sfTrue);
}

bool my_paint(void)
{
    my_paint_t *my_paint = malloc(sizeof(my_paint_t));

    if (!my_paint)
        return false;
    my_paint->window = create_window(WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
    my_paint->gui.button[0] = create_button((button_options_t){
        {100, 100},
        {750, 400},
        sfRed,
        "Hello"
    }, print_action);
    init_canva(my_paint);
    while (sfRenderWindow_isOpen(my_paint->window.window)) {
        event_loop(my_paint->window.window, my_paint->window.event, my_paint);
        display(my_paint);
    }
    destroy(my_paint);
    return true;
}
