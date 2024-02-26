/*
** EPITECH PROJECT, 2024
** my_paint
** File description:
** my_paint.h
*/

#ifndef MY_PAINT_MY_PAINT_H
    #define MY_PAINT_MY_PAINT_H

    #include <SFML/Graphics.h>
    #include <SFML/Window.h>
    #include <SFML/System.h>
    #include "my.h"

    #define WIN_WIDTH 1920
    #define WIN_HEIGHT 1080
    #define WIN_TITLE "My_Paint"

typedef struct window_s {
    sfRenderWindow *window;
    sfVideoMode mode;
    sfEvent event;
    sfView *view;
} window_t;

typedef struct my_paint_s {
    window_t window;
} my_paint_t;

bool my_paint(void);

window_t create_window(int width, int height, char *title);
void event_loop(sfRenderWindow *window, sfEvent event, my_paint_t *my_paint);

#endif //MY_PAINT_MY_PAINT_H
