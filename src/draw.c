/*
** EPITECH PROJECT, 2024
** my_paint
** File description:
** event.c
*/

#include "my_paint.h"

void update_pixel(my_paint_t *my_paint, int xi, int yj)
{
    int pixel = (yj * 1920 + xi) * 4;

    my_paint->canva.canva_pixels[pixel] = my_paint->tools.actual_tools == 1 ?
        255 : my_paint->tools.rgba[0];
    my_paint->canva.canva_pixels[pixel + 1] = my_paint->tools.actual_tools == 1
    ? 255 : my_paint->tools.rgba[1];
    my_paint->canva.canva_pixels[pixel + 2] = my_paint->tools.actual_tools == 1
    ? 255 : my_paint->tools.rgba[2];
    my_paint->canva.canva_pixels[pixel + 3] = my_paint->tools.actual_tools == 1
    ? 0 : my_paint->tools.rgba[3];
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

    for (int j = -my_paint->tools.size; j <= my_paint->tools.size; j++) {
        xi = x + i;
        yj = y + j;
        if (xi >= 0 && xi < 1920 && yj >= 0 && yj < 1080) {
            update_pixel(my_paint, xi, yj);
        }
    }
}

static void draw_at_point_circle_two(my_paint_t *my_paint,
    sfVector2i pos, int i, int j)
{
    int xi = pos.x + i;
    int yj = pos.y + j;

    if (i * i + j * j <= my_paint->tools.size * my_paint->tools.size) {
        if (xi >= 0 && xi < 1920 && yj >= 0 && yj < 1080) {
            update_pixel(my_paint, xi, yj);
        }
    }
}

static void draw_at_point_circle(my_paint_t *my_paint, int x, int y)
{
    my_paint->draw_params.min_x = 1920;
    my_paint->draw_params.min_y = 1080;
    my_paint->draw_params.max_x = 0;
    my_paint->draw_params.max_y = 0;
    for (int i = -my_paint->tools.size; i <= my_paint->tools.size; i++) {
        for (int j = -my_paint->tools.size; j <= my_paint->tools.size; j++) {
            draw_at_point_circle_two(my_paint, (sfVector2i){x, y}, i, j);
        }
    }
    sfTexture_updateFromPixels(my_paint->canva.canva_texture,
    my_paint->canva.canva_pixels, my_paint->draw_params.max_x -
    my_paint->draw_params.min_x + 1,
    my_paint->draw_params.max_y - my_paint->draw_params.min_y + 1,
    my_paint->draw_params.min_x, my_paint->draw_params.min_y);
}

void draw_at_point_square(my_paint_t *my_paint, int x, int y)
{
    my_paint->draw_params.min_x = 1920;
    my_paint->draw_params.min_y = 1080;
    my_paint->draw_params.max_x = 0;
    my_paint->draw_params.max_y = 0;
    for (int i = -my_paint->tools.size; i <= my_paint->tools.size; i++)
        draw_in_bounds(my_paint, x, y, i);
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
        if (my_paint->tools.square == 0) {
            draw_at_point_circle(my_paint, x, y);
        } else
            draw_at_point_square(my_paint, x, y);
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

static void drawing_loop_two(my_paint_t *my_paint, sfBool *was_mouse_pressed,
    sfEvent event)
{
    if (*was_mouse_pressed) {
        if (my_paint->tools.square == 0) {
            draw_at_point_circle(my_paint, my_paint->canva.curr_mouse_pos.x,
                my_paint->canva.curr_mouse_pos.y);
        }
        if (my_paint->tools.square == 1) {
            draw_at_point_square(my_paint, my_paint->canva.curr_mouse_pos.x,
                my_paint->canva.curr_mouse_pos.y);
        }
        if (my_paint->tools.square == 2)
            if_line(my_paint, was_mouse_pressed);
        if (my_paint->tools.square == 3)
            draw_rectangle(my_paint, event, WINDOW);
        if (my_paint->tools.square == 4)
            draw_circle(my_paint, event, WINDOW);
        if (my_paint->tools.square == 5)
            draw_sim_line(my_paint, event, WINDOW);
        *was_mouse_pressed = sfFalse;
    }
}

static int undo_save(my_paint_t *my_paint)
{
    if (my_paint->undoredo.actual == 10) {
        free(my_paint->undoredo.canva_pixels[0]);
        for (int i = 0; i < 9; i++) {
            my_paint->undoredo.canva_pixels[i] =
            my_paint->undoredo.canva_pixels[i + 1];
        }
        my_paint->undoredo.canva_pixels[9] = malloc(1920 * 1080 * 4);
        my_memcpy(my_paint->undoredo.canva_pixels[9],
        my_paint->canva.canva_pixels, 1920 * 1080 * 4);
    } else {
        my_paint->undoredo.canva_pixels[my_paint->undoredo.actual] =
        malloc(1920 * 1080 * 4);
        my_memcpy(my_paint->undoredo.canva_pixels[my_paint->undoredo.actual],
        my_paint->canva.canva_pixels, 1920 * 1080 * 4);
        my_paint->undoredo.actual++;
    }
}

void drawing_loop(my_paint_t *my_paint, sfEvent event)
{
    static sfBool was_mouse_pressed = sfFalse;
    sfVector2i mouse_pos =
        sfMouse_getPositionRenderWindow(my_paint->window.window);
    sfVector2u window_size = sfRenderWindow_getSize(my_paint->window.window);
    sfVector2f scale = {1920.0f / window_size.x, 1080.0f / window_size.y};

    button_pressed(&was_mouse_pressed, my_paint);
    if (my_paint->canva.canva_drawing) {
        my_paint->canva.prev_mouse_pos = my_paint->canva.curr_mouse_pos;
        my_paint->canva.curr_mouse_pos.x = mouse_pos.x * scale.x;
        my_paint->canva.curr_mouse_pos.y = mouse_pos.y * scale.y;
        if (was_mouse_pressed) {
            undo_save(my_paint);
            drawing_loop_two(my_paint, &was_mouse_pressed, event);
        } else
            draw_not_pressed(my_paint);
    }
}
