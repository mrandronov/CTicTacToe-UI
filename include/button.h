#ifndef __LIB_BUTTON_H__
#define __LIB_BUTTON_H__

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "SDL2/SDL.h"

#include "color.h"
#include "config.h"

#define BUTTON_LIST_SIZE 10

typedef struct
{
        SDL_Rect                box;
        SDL_Color*              color;
        SDL_Color*              highlight_color;
        SDL_Color*              selected_color;
        int                     is_highlighted;
        int                     is_pressed;
        int                     (*pressFunc)();
} button_t;

button_t* button_list_init( SDL_Renderer* renderer, config_t* config );

button_t* button_create( int x,
        int y,
        int w,
        int h,
        SDL_Color* color,
        SDL_Color* highlight,
        SDL_Color* select,
        int (*pressFunc)() );

void draw_button( SDL_Renderer* renderer, button_t* button );

void button_destroy( button_t* button );

void press_buttons();

void unpress_buttons();

void handle_button_press();

void draw_button_list( SDL_Renderer* renderer );

void highlight_buttons();

void button_list_destroy();

#endif /* __LIB_BUTTON_H__ */
