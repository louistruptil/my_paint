/*
** EPITECH PROJECT, 2024
** my_paint
** File description:
** my_paint.c
*/

#include "my_paint.h"

void destroy(my_paint_t *my_paint)
{
    for (int i = 0; i < BUTTON_COUNT; i++)
        destroy_button(my_paint->gui.button[i]);
    sfRenderWindow_destroy(WINDOW);
    free(my_paint);
}

void display_canva(my_paint_t *my_paint)
{
    sfVector2u windowSize = sfRenderWindow_getSize(my_paint->window.window);
    sfVector2f scale = {(float)windowSize.x / my_paint->tools.canva_scale.x,
    (float)windowSize.y / my_paint->tools.canva_scale.y};
    sfVector2f spritePos = {windowSize.x / 2.0f, windowSize.y / 2.0f};

    sfSprite_setScale(my_paint->canva.canva_sprite, scale);
    sfSprite_setPosition(my_paint->canva.canva_sprite, spritePos);
    sfTexture_updateFromPixels(my_paint->canva.canva_texture,
    my_paint->canva.canva_pixels, 1920, 1080, 0, 0);
    sfRenderWindow_drawSprite(my_paint->window.window,
    my_paint->canva.canva_sprite, NULL);
}

static void display_ui(my_paint_t *my_paint)
{
    sfVector2u windowSize = sfRenderWindow_getSize(WINDOW);
    sfVector2f leftBarSize;
    sfVector2f leftBarPos;
    sfVector2f topBarSize;
    sfVector2f topBarPos;

    leftBarSize = (sfVector2f){windowSize.x * 0.04, windowSize.y};
    sfRectangleShape_setSize(my_paint->interface.left_bar, leftBarSize);
    leftBarPos = (sfVector2f){0, 0};
    sfRectangleShape_setPosition(my_paint->interface.left_bar, leftBarPos);
    topBarSize = (sfVector2f){windowSize.x, windowSize.y * 0.04};
    sfRectangleShape_setSize(my_paint->interface.top_bar, topBarSize);
    topBarPos = (sfVector2f){0, 0};
    sfRectangleShape_setPosition(my_paint->interface.top_bar, topBarPos);
    sfRenderWindow_drawRectangleShape(WINDOW,
        my_paint->interface.left_bar, NULL);
    sfRenderWindow_drawRectangleShape(WINDOW,
        my_paint->interface.top_bar, NULL);
}

void display(my_paint_t *my_paint)
{
    sfRenderWindow_clear(WINDOW, sfWhite);
    display_canva(my_paint);
    display_ui(my_paint);
    my_paint->can_draw = true;
    for (int i = 0; i < BUTTON_COUNT; i++)
        display_button(my_paint, my_paint->gui.button[i]);
    for (int i = 0; i < 9; i++)
        display_button(my_paint, my_paint->gui.color_palette[i]);
    for (int i = 0; i < DROPDOWN_COUNT; i++)
        display_dropdown(my_paint, my_paint->gui.dropdown[i]);
    if (my_paint->tools.color_selector) {
        sfRenderWindow_drawRectangleShape(WINDOW,
            my_paint->gui.color_selector.rect, NULL);
        sfRenderWindow_drawRectangleShape(WINDOW,
            my_paint->gui.color_selector.selected_color, NULL);
    }
    display_popup(my_paint);
    if (my_paint->tools.actual_tools == 4)
        sfRenderWindow_drawRectangleShape(WINDOW, SELECT_RECT, NULL);
    sfRenderWindow_display(WINDOW);
}

static void init_canva(my_paint_t *my_paint)
{
    sfVector2f spriteOrigin;
    sfVector2u windowSize;
    sfVector2f spritePos;

    my_paint->canva.canva_pixels = malloc(1920 * 1080 * 4);
    for (int i = 0; i < 1920 * 1080 * 4; i += 4) {
        my_paint->canva.canva_pixels[i] = 255;
        my_paint->canva.canva_pixels[i + 1] = 255;
        my_paint->canva.canva_pixels[i + 2] = 255;
        my_paint->canva.canva_pixels[i + 3] = 0;
    }
    my_paint->canva.canva_texture = sfTexture_create(1920, 1080);
    my_paint->canva.canva_sprite = sfSprite_create();
    sfSprite_setTexture(my_paint->canva.canva_sprite,
        my_paint->canva.canva_texture, sfTrue);
    spriteOrigin = (sfVector2f){1920 / 2.0f, 1080 / 2.0f};
    sfSprite_setOrigin(my_paint->canva.canva_sprite, spriteOrigin);
    windowSize = sfRenderWindow_getSize(my_paint->window.window);
    spritePos = (sfVector2f){windowSize.x / 2.0f, windowSize.y / 2.0f};
    sfSprite_setPosition(my_paint->canva.canva_sprite, spritePos);
}

static void init_tool_tab(my_paint_t *my_paint)
{
    my_paint->tools.rgba = malloc(sizeof(int) * 4);
    my_paint->tools.rgba[0] = 0;
    my_paint->tools.rgba[1] = 0;
    my_paint->tools.rgba[2] = 0;
    my_paint->tools.rgba[3] = 255;
    my_paint->tools.square = 1;
    my_paint->tools.actual_tools = 0;
    my_paint->tools.size = 5;
    my_paint->window.popup_size.popup_text = (sfText *)my_strdup("");
    my_paint->window.popup_open.popup_text = (sfText *)my_strdup("");
    my_paint->window.popup_save.popup_text = (sfText *)my_strdup("");
    my_paint->tools.tools[0] = my_strdup("pen");
    my_paint->tools.tools[1] = my_strdup("eraser");
    my_paint->tools.canva_scale.x = 1920.0f;
    my_paint->tools.canva_scale.y = 1080.0f;
    my_paint->tools.color_selector = false;
}

bool my_paint(void)
{
    my_paint_t *my_paint = malloc(sizeof(my_paint_t));

    my_paint->window = create_window(WIN_WIDTH,
        WIN_HEIGHT, WIN_TITLE);
    my_paint->can_draw = true;
    init_tool_tab(my_paint);
    create_interface(my_paint);
    init_canva(my_paint);
    main_loop(my_paint);
    destroy(my_paint);
    return true;
}
