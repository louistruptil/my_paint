/*
** EPITECH PROJECT, 2024
** my_paint
** File description:
** event.c
*/

#include "my_paint.h"

static void lin_act(my_paint_t *my_paint)
{
    my_paint->tools.actual_tools = 0;
    my_paint->tools.square = 5;
}

void btn_lin(my_paint_t *my_paint)
{
    my_paint->gui.button[11] = create_button((button_options_t) {
        {20, 450},
        {32, 32},
        sfColor_fromRGB(255, 255, 255),
        NULL,
        sfColor_fromRGB(255, 255, 255),
        "assets/line.png"
    }, lin_act, NULL);
}

static sfVector2i get_world_pos(my_paint_t *my_paint, sfRenderWindow* window)
{
    sfVector2i pixelPos = sfMouse_getPositionRenderWindow(window);

    return my_paint->canva.curr_mouse_pos;
}

static void update_start_point(sfVector2i *start_point,
    sfVector2i worldPos, sfBool *is_first_click)
{
    *start_point = (sfVector2i){worldPos.x, worldPos.y};
    *is_first_click = sfFalse;
}

static void update_end_point(sfVector2i *end_point,
    sfVector2i worldPos, sfBool *is_first_click)
{
    *end_point = (sfVector2i){worldPos.x, worldPos.y};
    *is_first_click = sfTrue;
}

static void calculate_line(my_paint_t *my_paint,
    sfVector2i start_point, sfVector2i end_point)
{
    int dx = abs(end_point.x - start_point.x);
    int dy = abs(end_point.y - start_point.y);
    int sx = (start_point.x < end_point.x) ? 1 : -1;
    int sy = (start_point.y < end_point.y) ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2, e2;

    while (1) {
        draw_at_point_square(my_paint, start_point.x, start_point.y);
        if (start_point.x == end_point.x && start_point.y == end_point.y)
            break;
        e2 = err;
        if (e2 > -dx) {
            err -= dy;
            start_point.x += sx;
        }
        if (e2 < dy) {
            err += dx;
            start_point.y += sy;
        }
    }
}

void draw_sim_line(my_paint_t *my_paint, sfEvent event, sfRenderWindow* window)
{
    static sfVector2i start_point;
    static sfVector2i end_point;
    static sfBool is_first_click = sfTrue;
    sfVector2i worldPos;

    if (event.type == sfEvtMouseButtonPressed) {
        worldPos = get_world_pos(my_paint, window);
        if (is_first_click) {
            update_start_point(&start_point, worldPos, &is_first_click);
        } else {
            update_end_point(&end_point, worldPos, &is_first_click);
            calculate_line(my_paint, start_point, end_point);
        }
    }
}
