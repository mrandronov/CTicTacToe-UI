#ifndef __LIB_LABEL_H__
#define __LIB_LABEL_H__

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#include "color.h"
#include "config.h"

#define LABEL_LIST_SIZE 10
#define DYNAMIC_LABEL_LIST_SIZE 10

typedef struct
{
    SDL_Texture* texture; 
    SDL_Rect rect;
} label_t;

int get_label_index();

label_t* label_create( SDL_Renderer* renderer, const char* str, int x, int y, int size );

void label_draw( SDL_Renderer* renderer, label_t* label );

void label_destroy( label_t* label );

label_t** label_list_init( SDL_Renderer* renderer, config_t* game_config );

void draw_label_list( SDL_Renderer* renderer );

void label_list_destroy_from_index( int start_index );

void label_list_destroy();

int increment_player_score();

int increment_computer_score();

void reset_player_score();

void reset_computer_score();

void set_status_message( char* msg );

label_t** dynamic_labels_list_init();

void dynamic_labels_destroy();

void draw_dynamic_labels( SDL_Renderer* renderer );

#endif /* __LIB_LABEL_H__ */
