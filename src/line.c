/*
** EPITECH PROJECT, 2024
** my_paint
** File description:
** event.c
*/

#include "my_paint.h"

static void line_act(my_paint_t *my_paint)
{
    my_paint->tools.actual_tools = 0;
    my_paint->tools.square = 2;
}

void btn_line(my_paint_t *my_paint)
{
    my_paint->gui.button[8] = create_button((button_options_t) {
        {20, 450},
        {32, 32},
        sfColor_fromRGB(255, 255, 255),
        NULL,
        sfColor_fromRGB(255, 255, 255),
        "assets/line.png"
    }, line_act, NULL);
}

static void draw_line(my_paint_t *my_paint, sfVector2i point1,
    sfVector2i point2)
{
    int dx = abs(point2.x - point1.x);
    int sx = point1.x < point2.x ? 1 : -1;
    int dy = abs(point2.y - point1.y);
    int sy = point1.y < point2.y ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2, e2;

    while (1) {
        draw_at_point_square(my_paint, point1.x, point1.y);
        if (point1.x == point2.x && point1.y == point2.y)
            break;
        e2 = err;
        if (e2 > -dx) {
            err -= dy;
            point1.x += sx;
        }
        if (e2 < dy) {
            err += dx;
            point1.y += sy;
        }
    }
}

void if_line(my_paint_t *my_paint, sfBool *was_mouse_pressed)
{
    if (sfMouse_isButtonPressed(sfMouseLeft)) {
        if (my_paint->canva.prev_mouse_pos.x == 0 &&
        my_paint->canva.prev_mouse_pos.y == 0)
            my_paint->canva.prev_mouse_pos = my_paint->canva.curr_mouse_pos;
        if (*was_mouse_pressed) {
            draw_line(my_paint, my_paint->canva.prev_mouse_pos,
            my_paint->canva.curr_mouse_pos);
            my_paint->canva.prev_mouse_pos =
            my_paint->canva.curr_mouse_pos;
        }
        *was_mouse_pressed = sfTrue;
    } else
        *was_mouse_pressed = sfFalse;
}
