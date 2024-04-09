#ifndef __LIB_COLOR_H__
#define __LIB_COLOR_H__

SDL_Color clear;
SDL_Color white;
SDL_Color background;
SDL_Color default_color;
SDL_Color highlight_color;
SDL_Color select_color;
SDL_Color press_color;
SDL_Color orange;
SDL_Color green;

void color_init( char* theme_path );

void set_color( SDL_Renderer* renderer, SDL_Color color );

#endif /* __LIB_COLOR_H__ */
