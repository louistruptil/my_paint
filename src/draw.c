/*
** EPITECH PROJECT, 2024
** my_paint
** File description:
** event.c
*/

#include "my_paint.h"

static void update_pixel(my_paint_t *my_paint, int xi, int yj)
{
    int pixel_index = (yj * 1920 + xi) * 4;

    my_paint->canva.canva_pixels[pixel_index] = my_paint->tools.rgba[0];
    my_paint->canva.canva_pixels[pixel_index + 1] = my_paint->tools.rgba[1];
    my_paint->canva.canva_pixels[pixel_index + 2] = my_paint->tools.rgba[2];
    my_paint->canva.canva_pixels[pixel_index + 3] = my_paint->tools.rgba[3];
    if (xi < my_paint->draw_params.min_x)
        my_paint->draw_params.min_x = xi;
    if (xi > my_paint->draw_params.max_x)
        my_paint->draw_params.max_x = xi;
    if (yj < my_paint->draw_params.min_y)
        my_paint->draw_params.min_y = yj;
    if (yj > my_paint->draw_params.max_y)
        my_paint->draw_params.max_y = yj;
}

static void draw_in_bounds(my_paint_t *my_paint, int x, int y, int i)
{
    int xi;
    int yj;
    int brush_size = 10;

    for (int j = -brush_size; j <= brush_size; j++) {
        xi = x + i;
        yj = y + j;
        if (xi >= 0 && xi < 1920 && yj >= 0 && yj < 1080) {
            update_pixel(my_paint, xi, yj);
        }
    }
}

static void draw_at_point(my_paint_t *my_paint, int x, int y)
{
    int brush_size = 10;

    my_paint->draw_params.min_x = 1920;
    my_paint->draw_params.min_y = 1080;
    my_paint->draw_params.max_x = 0;
    my_paint->draw_params.max_y = 0;
    for (int i = -brush_size; i <= brush_size; i++) {
        draw_in_bounds(my_paint, x, y, i);
    }
    sfTexture_updateFromPixels(my_paint->canva.canva_texture,
    my_paint->canva.canva_pixels, my_paint->draw_params.max_x -
    my_paint->draw_params.min_x + 1,
    my_paint->draw_params.max_y - my_paint->draw_params.min_y + 1,
    my_paint->draw_params.min_x, my_paint->draw_params.min_y);
}

static void draw_not_pressed(my_paint_t *my_paint)
{
    int dx = my_paint->canva.curr_mouse_pos.x -
    my_paint->canva.prev_mouse_pos.x;
    int dy = my_paint->canva.curr_mouse_pos.y -
    my_paint->canva.prev_mouse_pos.y;
    int max_steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float t;
    int x;
    int y;

    for (int step = 0; step <= max_steps; step++) {
        t = (float)step / max_steps;
        x = my_paint->canva.prev_mouse_pos.x + t * dx;
        y = my_paint->canva.prev_mouse_pos.y + t * dy;
        draw_at_point(my_paint, x, y);
    }
}

static void button_pressed(sfBool *was_mouse_pressed, my_paint_t *my_paint)
{
    if (sfMouse_isButtonPressed(sfMouseLeft)) {
        if (!my_paint->canva.canva_drawing)
            *was_mouse_pressed = sfTrue;
        my_paint->canva.canva_drawing = sfTrue;
    } else
        my_paint->canva.canva_drawing = sfFalse;
}

void drawing_loop(my_paint_t *my_paint, sfEvent event)
{
    static sfBool was_mouse_pressed = sfFalse;

    button_pressed(&was_mouse_pressed, my_paint);
    if (my_paint->canva.canva_drawing) {
        my_paint->canva.prev_mouse_pos = my_paint->canva.curr_mouse_pos;
        sfVector2i mousePos = sfMouse_getPositionRenderWindow(my_paint->window.window);
        sfVector2u windowSize = sfRenderWindow_getSize(my_paint->window.window);
        sfVector2f scale = {1920.0f / windowSize.x, 1080.0f / windowSize.y};
        my_paint->canva.curr_mouse_pos.x = mousePos.x * scale.x;
        my_paint->canva.curr_mouse_pos.y = mousePos.y * scale.y;
        if (was_mouse_pressed) {
            draw_at_point(my_paint, my_paint->canva.curr_mouse_pos.x,
            my_paint->canva.curr_mouse_pos.y);
            was_mouse_pressed = sfFalse;
        } else {
            draw_not_pressed(my_paint);
        }
    }
}
