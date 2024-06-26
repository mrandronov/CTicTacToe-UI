#ifndef __LIB_SELECTOR_H__
#define __LIB_SELECTOR_H__

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "SDL2/SDL.h"

#include "color.h"
#include "config.h"

#define SELECTOR_LIST_SIZE 50

typedef struct SELECTOR
{
        SDL_Rect                box;
        SDL_Color*              color;
        SDL_Color*              highlight_color;
        SDL_Color*              selected_color;
        SDL_Color*              pressed_color;
        int                     is_highlighted;
        int                     is_selected;
        int                     is_pressed;
        int                     is_disabled;
        int                     (*pressFunc)( struct SELECTOR* );
        int                     (*unpressFunc)( struct SELECTOR* );
} selector_t;

int get_selector_index();

selector_t* selector_list_init( SDL_Renderer* renderer, config_t* config );

selector_t* selector_init( SDL_Renderer* renderer,
                        int x,
                        int y,
                        int w,
                        int h,
                        SDL_Color* color,
                        SDL_Color* highlight,
                        SDL_Color* select,
                        SDL_Color* press,
                        const char* text,
                        int (*pressFunc)(),
                        int (*unpressFunc)() );

void draw_selector( SDL_Renderer* renderer, selector_t* selector );

void selector_destroy( selector_t* s );

void press_selectors();

void unpress_selectors();

void handle_selector_press();

void draw_selector_list( SDL_Renderer* renderer );

void highlight_selectors();

selector_t* get_selector( selector_t* s );

void selector_list_destroy_from_index( int start_index );

void selector_list_destroy();

#endif /* __LIB_SELECTOR_H__ */
