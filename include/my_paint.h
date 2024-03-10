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
    #include <SFML/Audio.h>
    #include <SFML/Network.h>
    #include "my.h"
    #include <math.h>

    #define WIN_WIDTH 1920
    #define WIN_HEIGHT 1080
    #define WIN_TITLE "My_Paint"

    #define CANVA_WIDTH 1920
    #define CANVA_HEIGHT 1080

    #define BUTTON_COUNT 3
    #define DROPDOWN_COUNT 4

    #define WINDOW my_paint->window.window

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
    sfColor text_color;
    char *img;
} button_options_t;

typedef struct button_s {
    sfRectangleShape *rect;
    sfText *text;
    sfFont *font;
    bool (*is_clicked)(struct button_s *, sfMouseButtonEvent *);
    bool (*is_hover)(struct button_s *, sfMouseMoveEvent *);
    void (*action)(my_paint_t *my_paint, struct button_s *);
    void (*hover)(struct button_s *);
    enum e_gui_state state;
    button_options_t options;
    sfTexture *img_texture;
} button_t;

typedef struct drop_down_item_s {
    struct button_s *button;
    struct drop_down_item_s *next;
} drop_down_item_t;

typedef struct drop_down_s {
    struct button_s *button;
    drop_down_item_t *items;
    bool is_open;
} drop_down_t;

typedef struct gui_s {
    button_t *button[BUTTON_COUNT];
    drop_down_t *dropdown[DROPDOWN_COUNT];
} gui_t;

typedef struct canva_s {
    sfTexture *canva_texture;
    sfUint8* canva_pixels;
    sfSprite *canva_sprite;
    sfBool canva_drawing;
    sfVector2i prev_mouse_pos;
    sfVector2i curr_mouse_pos;
} canva_t;

typedef struct window_s {
    sfRenderWindow *window;
    sfVideoMode mode;
    sfEvent event;
    sfView *view;
    int display_popup;
    sfRectangleShape *popup;
    sfText *popup_text;
    char *popup_text_str;
} window_t;

typedef struct draw_params_s {
    int min_x;
    int min_y;
    int max_x;
    int max_y;
} draw_params_t;

typedef struct interface_s {
    sfRectangleShape *left_bar;
    sfRectangleShape *top_bar;
} interface_t;

typedef struct tools_s {
    char *tools[2];
    int *rgba;
    int actual_tools;
    int square;
    int size;
} tools_t;

typedef struct my_paint_s {
    window_t window;
    gui_t gui;
    canva_t canva;
    draw_params_t draw_params;
    interface_t interface;
    tools_t tools;
} my_paint_t;

bool my_paint(void);

window_t create_window(int width, int height, char *title);
void event_loop(sfRenderWindow *window, sfEvent event, my_paint_t *my_paint);
int main_loop(my_paint_t *my_paint);

int create_interface(my_paint_t *my_paint);
button_t *create_button(button_options_t options,
    void (*action)(my_paint_t *, button_t *), void (*hover)(button_t *));
bool is_button_clicked(button_t *button, sfMouseButtonEvent *event);
bool is_button_hover(button_t *button, sfMouseMoveEvent *event);
void destroy_button(button_t *button);
void display_button(sfRenderWindow *window, button_t *button);

drop_down_t *create_dropdown(button_options_t options);
void add_item_to_dropdown(drop_down_t *dropdown, button_options_t options,
    void (*action)(my_paint_t *, button_t *), void (*hover)(button_t *));
void display_dropdown(sfRenderWindow *window, drop_down_t *dropdown);
int color_picker(my_paint_t *my_paint, sfEvent event);

void drawing_loop(my_paint_t *my_paint, sfEvent event);
void handle_resize_interface(my_paint_t *my_paint, sfEvent event);

sfColor get_pixel_color(const my_paint_t *my_paint, const int x, const int y);
void set_pixel_color(my_paint_t *my_paint, const int x, const int y,
    const sfColor color);
void flood_fill(my_paint_t *my_paint, int x, int y, sfColor new_color);

void do_select_action(my_paint_t *my_paint, sfEvent event);
void write_for_popup(my_paint_t *my_paint, sfEvent event);


#endif //MY_PAINT_MY_PAINT_H
