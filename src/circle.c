/*
** EPITECH PROJECT, 2024
** my_paint
** File description:
** event.c
*/

#include "my_paint.h"

static void cir_act(my_paint_t *my_paint, button_t *button)
{
    my_paint->tools.actual_tools = 0;
    my_paint->tools.square = 4;
}

void btn_cir(my_paint_t *my_paint)
{
    my_paint->gui.button[10] = create_button((button_options_t) {
        {20, 560},
        {32, 32},
        sfColor_fromRGB(255, 255, 255),
        NULL,
        sfColor_fromRGB(255, 255, 255),
        "assets/circle_drow.png"
    }, cir_act, NULL);
}

static void draw_circle4(my_paint_t *my_paint, int draw_x, int draw_y)
{
    if (draw_x >= 0 && draw_x < 1920 && draw_y >= 0 && draw_y < 1080)
        update_pixel(my_paint, draw_x, draw_y);
}

static void draw_circle3(my_paint_t *my_paint, int radius,
    int y, sfVector2i center)
{
    int draw_x;
    int draw_y;

    for (int x = -radius; x <= radius; x++) {
        if (x * x + y * y <= radius * radius) {
            draw_x = center.x + x;
            draw_y = center.y + y;
            draw_circle4(my_paint, draw_x, draw_y);
        }
    }
}

static void draw_circle2(my_paint_t *my_paint, sfVector2i center,
    sfVector2i point, sfRenderWindow* window)
{
    int radius = sqrt(pow(point.x - center.x, 2) + pow(point.y - center.y, 2));

    for (int y = -radius; y <= radius; y++)
        draw_circle3(my_paint, radius, y, center);
}

void draw_circle(my_paint_t *my_paint, sfEvent event, sfRenderWindow* window)
{
    static sfVector2i center;
    static sfBool is_first_click = sfTrue;
    sfVector2i point;
    sfVector2i world_pos;
    sfVector2i pixel_pos;

    if (event.type == sfEvtMouseButtonPressed) {
        pixel_pos = sfMouse_getPositionRenderWindow(window);
        world_pos = my_paint->canva.curr_mouse_pos;
        if (is_first_click) {
            center = (sfVector2i){world_pos.x, world_pos.y};
            is_first_click = sfFalse;
        } else {
            point = (sfVector2i){world_pos.x, world_pos.y};
            is_first_click = sfTrue;
            draw_circle2(my_paint, center, point, WINDOW);
        }
    }
}
