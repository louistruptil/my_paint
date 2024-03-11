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
    sfSprite_setScale(my_paint->canva.canva_sprite, (sfVector2f){windowSize.x / 1920.0f, windowSize.y / 1080.0f});
    sfTexture_updateFromPixels(my_paint->canva.canva_texture,
    my_paint->canva.canva_pixels, 1920, 1080, 0, 0);
    sfRenderWindow_drawSprite(WINDOW,
    my_paint->canva.canva_sprite, NULL);
}

static void display_ui(my_paint_t *my_paint)
{
    sfVector2u windowSize = sfRenderWindow_getSize(WINDOW);

    sfVector2f leftBarSize = {windowSize.x * 0.04, windowSize.y}; // 5% of window width
    sfRectangleShape_setSize(my_paint->interface.left_bar, leftBarSize);
    sfVector2f leftBarPos = {0, 0};
    sfRectangleShape_setPosition(my_paint->interface.left_bar, leftBarPos);

    sfVector2f topBarSize = {windowSize.x, windowSize.y * 0.04}; // 5% of window height
    sfRectangleShape_setSize(my_paint->interface.top_bar, topBarSize);
    sfVector2f topBarPos = {0, 0};
    sfRectangleShape_setPosition(my_paint->interface.top_bar, topBarPos);

    sfRenderWindow_drawRectangleShape(WINDOW, my_paint->interface.left_bar, NULL);
    sfRenderWindow_drawRectangleShape(WINDOW, my_paint->interface.top_bar, NULL);
}

static void display_popup(my_paint_t *my_paint)
{
    if (my_paint->window.display_popup == 1) {
        sfVector2u windowSize = sfRenderWindow_getSize(WINDOW);

        sfVector2f popupSize = {windowSize.x * 0.3f, windowSize.y * 0.3f}; // 30% of window size
        sfRectangleShape_setSize(my_paint->window.popup, popupSize);
        sfVector2f popupPosition = {windowSize.x / 2.0f - popupSize.x / 2.0f, windowSize.y / 2.0f - popupSize.y / 2.0f};
        sfRectangleShape_setPosition(my_paint->window.popup, popupPosition);

        sfText_setCharacterSize(my_paint->window.popup_text, popupSize.y * 0.1f); // 10% of popup height

        sfFloatRect textRect = sfText_getLocalBounds(my_paint->window.popup_text);
        sfVector2f textPosition = {
            popupPosition.x + (popupSize.x - textRect.width) / 2 - textRect.left,
            popupPosition.y + (popupSize.y - textRect.height) / 2 - textRect.top
        };
        sfText_setPosition(my_paint->window.popup_text, textPosition);

        sfRenderWindow_drawRectangleShape(WINDOW, my_paint->window.popup, NULL);
        sfRenderWindow_drawText(WINDOW, my_paint->window.popup_text, NULL);
    }
}

void display(my_paint_t *my_paint)
{
    sfRenderWindow_clear(WINDOW, sfWhite);
    display_canva(my_paint);
    display_ui(my_paint);
    my_paint->can_draw = true;
    for (int i = 0; i < BUTTON_COUNT; i++) {
        display_button(my_paint, my_paint->gui.button[i]);
    }
    for (int i = 0; i < 9; i++) {
        display_button(my_paint, my_paint->gui.color_palette[i]);
    }
    for (int i = 0; i < DROPDOWN_COUNT; i++) {
        display_dropdown(my_paint, my_paint->gui.dropdown[i]);
    }
    display_popup(my_paint);
    sfRenderWindow_display(WINDOW);
}

// Callack function when button clicked create one for each button
static void print_action(my_paint_t *my_paint, button_t *button)
{
    my_putstr("Button clicked\n");
    for (int i = 0; i < 1920 * 1080 * 4; i += 4) {
        my_paint->canva.canva_pixels[i] = 255;
        my_paint->canva.canva_pixels[i + 1] = 255;
        my_paint->canva.canva_pixels[i + 2] = 255;
        my_paint->canva.canva_pixels[i + 3] = 255;
    }
}

// Callack function when button hovered create one for each button
static void hover_action(button_t *button)
{
    sfRectangleShape_setSize(button->rect, (sfVector2f){200, 200});
}

static void init_canva(my_paint_t *my_paint)
{
    my_paint->canva.canva_pixels = malloc(1920 * 1080 * 4);
    for (int i = 0; i < 1920 * 1080 * 4; i += 4) {
        my_paint->canva.canva_pixels[i] = 255;
        my_paint->canva.canva_pixels[i + 1] = 255;
        my_paint->canva.canva_pixels[i + 2] = 255;
        my_paint->canva.canva_pixels[i + 3] = 255;
    }
    my_paint->canva.canva_texture = sfTexture_create(1920, 1080);
    my_paint->canva.canva_sprite = sfSprite_create();
    sfSprite_setTexture(my_paint->canva.canva_sprite,
    my_paint->canva.canva_texture, sfTrue);
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
    my_paint->window.popup_text = my_strdup("");
    my_paint->tools.tools[0] = my_strdup("pen");
    my_paint->tools.tools[1] = my_strdup("eraser");
}

bool my_paint(void)
{
    my_paint_t *my_paint = malloc(sizeof(my_paint_t));

    if (!my_paint)
        return false;
    my_paint->window = create_window(WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
    my_paint->can_draw = true;
    init_tool_tab(my_paint);
    create_interface(my_paint);
    init_canva(my_paint);
    main_loop(my_paint);
    destroy(my_paint);
    return true;
}
