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

static void draw_circle4(my_paint_t *my_paint, int drawX, int drawY)
{
    if (drawX >= 0 && drawX < 1920 && drawY >= 0 && drawY < 1080)
        update_pixel(my_paint, drawX, drawY);
}

static void draw_circle3(my_paint_t *my_paint, int radius,
    int y, sfVector2i center)
{
    int drawX;
    int drawY;

    for (int x = -radius; x <= radius; x++) {
        if (x * x + y * y <= radius * radius) {
            drawX = center.x + x;
            drawY = center.y + y;
            draw_circle4(my_paint, drawX, drawY);
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
    sfVector2i worldPos;
    sfVector2i pixelPos;

    if (event.type == sfEvtMouseButtonPressed) {
        pixelPos = sfMouse_getPositionRenderWindow(window);
        worldPos = my_paint->canva.curr_mouse_pos;
        if (is_first_click) {
            center = (sfVector2i){worldPos.x, worldPos.y};
            is_first_click = sfFalse;
        } else {
            point = (sfVector2i){worldPos.x, worldPos.y};
            is_first_click = sfTrue;
            draw_circle2(my_paint, center, point, WINDOW);
        }
    }
}
