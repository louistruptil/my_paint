/*
** EPITECH PROJECT, 2024
** my_paint
** File description:
** my_paint.c
*/

#include <stdio.h>
#include "my_paint.h"

int save_canva(my_paint_t *my_paint, sfEvent event)
{
    sfImage *image = sfTexture_copyToImage(my_paint->canva.canva_texture);

    sfImage_saveToFile(image, "canva.jpg");
    sfImage_destroy(image);
    return 0;
}

static void hover_action(button_t *button)
{
    (void)button;
}

static void select_color_action(my_paint_t *my_paint, button_t *button)
{
    sfColor color = sfRectangleShape_getFillColor(button->rect);

    my_paint->tools.rgba[0] = color.r;
    my_paint->tools.rgba[1] = color.g;
    my_paint->tools.rgba[2] = color.b;
    my_paint->tools.rgba[3] = color.a;
}

static void color_selector_action(my_paint_t *my_paint, button_t *button)
{
    my_paint->tools.color_selector = !my_paint->tools.color_selector;
}

static void init_color_selector(my_paint_t *my_paint)
{
    my_paint->gui.button[6] = create_button((button_options_t) {
        {1600 - 35, 5},
        {32, 32},
        sfColor_fromRGB(255, 255, 255),
        NULL,
        sfColor_fromRGB(255, 255, 255),
        "assets/rgb_color.png"
    }, color_selector_action, hover_action);
}

void handle_resize_interface(my_paint_t *my_paint, sfEvent event)
{
    sfVector2u windowSize;
    sfVector2f position;

    if (event.type == sfEvtResized) {
        windowSize = (sfVector2u){event.size.width, event.size.height};
        sfRectangleShape_setSize(my_paint->interface.left_bar,
            (sfVector2f){50, windowSize.y});
        position = (sfVector2f){0, 0};
        sfRectangleShape_setPosition(my_paint->interface.left_bar, position);
        sfRectangleShape_setSize(my_paint->interface.top_bar,
            (sfVector2f){windowSize.x, 35});
        sfRectangleShape_setPosition(my_paint->interface.top_bar, position);
    }
}

void btn_color_palette(my_paint_t *my_paint)
{
    sfColor primary_colors[9] = {
        sfWhite, sfBlack, sfRed, sfGreen, sfBlue, sfYellow, sfMagenta, sfCyan,
        sfColor_fromRGB(85, 98, 120)
    };

    for (int i = 0; i < 9; i++) {
        my_paint->gui.color_palette[i] = create_button((button_options_t) {
            {1600 + (i * 35), 5},
            {32, 32},
            primary_colors[i],
            NULL,
        }, select_color_action, hover_action);
    }
    init_color_selector(my_paint);
}

static int create_interface_buttons(my_paint_t *my_paint)
{
    btn_file(my_paint);
    btn_edition(my_paint);
    btn_help(my_paint);
    btn_pen(my_paint);
    btn_eraser(my_paint);
    btn_size(my_paint);
    btn_picker(my_paint);
    btn_bucket(my_paint);
    btn_color_palette(my_paint);
    btn_zoom(my_paint);
    btn_dezoom(my_paint);
}

int create_interface(my_paint_t *my_paint)
{
    sfVector2u windowSize;
    sfVector2f position;
    sfColor color;

    my_paint->interface.left_bar = sfRectangleShape_create();
    windowSize = sfRenderWindow_getSize(my_paint->window.window);
    sfRectangleShape_setSize(my_paint->interface.left_bar,
        (sfVector2f){75, windowSize.y});
    color = (sfColor){3, 6, 48, 255};
    sfRectangleShape_setFillColor(my_paint->interface.left_bar, color);
    position = (sfVector2f){0, 0};
    sfRectangleShape_setPosition(my_paint->interface.left_bar, position);
    my_paint->interface.top_bar = sfRectangleShape_create();
    sfRectangleShape_setSize(my_paint->interface.top_bar,
        (sfVector2f){windowSize.x, 35});
    sfRectangleShape_setFillColor(my_paint->interface.top_bar, color);
    sfRectangleShape_setPosition(my_paint->interface.top_bar, position);
    create_interface_buttons(my_paint);
    create_popup(my_paint);
    return 0;
}
