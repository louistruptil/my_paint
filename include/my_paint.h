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

    #define BUTTON_COUNT 1

enum e_gui_state {
    NONE = 0,
    HOVER,
    PRESSED,
    RELEASED,
    DISABLED
};

typedef struct my_paint_s my_paint_t;

typedef struct button_options_s {
    sfVector2f pos;
    sfVector2f size;
    sfColor color;
    char *text;
    char *img;
} button_options_t;

typedef struct button_s {
    sfRectangleShape *rect;
    sfText *text;
    sfFont *font;
    bool (*is_clicked)(struct button_s *, sfMouseButtonEvent *);
    bool (*is_hover)(struct button_s *, sfMouseMoveEvent *);
    void (*action)(my_paint_t *my_paint);
    enum e_gui_state state;
} button_t;

typedef struct gui_s {
    button_t *button[BUTTON_COUNT];
} gui_t;

typedef struct window_s {
    sfRenderWindow *window;
    sfVideoMode mode;
    sfEvent event;
    sfView *view;
} window_t;

typedef struct my_paint_s {
    window_t window;
    gui_t gui;
} my_paint_t;

bool my_paint(void);

window_t create_window(int width, int height, char *title);
void event_loop(sfRenderWindow *window, sfEvent event, my_paint_t *my_paint);

button_t *create_button(button_options_t options,
    void (*action)(my_paint_t *));
bool is_button_clicked(button_t *button, sfMouseButtonEvent *event);
bool is_button_hover(button_t *button, sfMouseMoveEvent *event);
void destroy_button(button_t *button);
void display_button(sfRenderWindow *window, button_t *button);

#endif //MY_PAINT_MY_PAINT_H
