#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#include "error.h"
#include "global.h"
#include "color.h"
#include "board_display.h"
#include "button.h"
#include "mouse.h"
#include "selector.h"
#include "label.h"
#include "config.h"

#include "game/board.h"
#include "game/game.h"

const int               SCREEN_WIDTH = 600;
const int               SCREEN_HEIGHT = 800;
const char*             TITLE = "C GUI TEST";

const float             fps_cap = 60.0f;
const float             fps_cap_in_ms = 1000.0f / fps_cap;
uint64_t                start;
uint64_t                end;
float                   delta;

char*                   theme_path;

SDL_Window*             window;
SDL_Renderer*           renderer;
global_t*               global;
config_t*               config;

void
clean_up()
{
        selector_list_destroy();
        label_list_destroy();
        board_destroy();
        button_list_destroy();
        dynamic_labels_destroy();

        SDL_Quit();
}

void
handle_events( )
{
        SDL_Event event;
        while( SDL_PollEvent( &event ) )
        {
                if ( event.type == SDL_QUIT )
                {
                        config->is_game_running = false;
                }
                if ( event.type == SDL_KEYDOWN )
                {
                        if ( event.key.keysym.scancode == SDL_SCANCODE_Q )
                        {
                                config->is_game_running = false;
                        }
                }
                if ( event.type == SDL_MOUSEMOTION )
                {
                        highlight_buttons();
                        highlight_selectors();

                }
                if ( event.type == SDL_MOUSEBUTTONDOWN )
                {
                        if ( event.button.button == SDL_BUTTON_LEFT )
                        {
                                press_buttons();
                                press_selectors();
                        }
                }
                if ( event.type == SDL_MOUSEBUTTONUP )
                {
                        if ( event.button.button == SDL_BUTTON_LEFT )
                        {
                                unpress_buttons();
                                unpress_selectors();
                                handle_button_press();
                                handle_selector_press();
                        }
                }
        }
}

void
init()
{
        assert_msg( ( SDL_Init( SDL_INIT_VIDEO ) != 0 ), SDL_GetError() );

        window = SDL_CreateWindow( TITLE, 
	                SDL_WINDOWPOS_UNDEFINED, 
	                SDL_WINDOWPOS_UNDEFINED, 
	                SCREEN_WIDTH, 
	                SCREEN_HEIGHT, 
	                SDL_WINDOW_SHOWN );
        
        assert_msg( (window == NULL), SDL_GetError() );

        renderer = SDL_CreateRenderer( window,
                        -1,
                        SDL_RENDERER_ACCELERATED );

        assert_msg( (renderer == NULL), SDL_GetError() );

        assert_msg( ( TTF_Init() != 0 ), TTF_GetError() );

        global = global_init();
        config = config_init();

        color_init( theme_path );
        label_list_init( renderer, config );
        dynamic_labels_list_init();
        button_list_init( renderer, config );
        selector_list_init( renderer, config );
        board_init( renderer, config );
}

void
draw_all_components()
{
        draw_button_list( renderer );
        draw_selector_list( renderer );
        draw_label_list( renderer );
        draw_dynamic_labels( renderer );
}

int
main( int argc, char* argv[] )
{
        if ( argc != 1 )
        {
                theme_path = argv[ 1 ];
        }
        else
        {
                theme_path = "./themes/Default.th";
        }
        init();

        char winner = ' ';

        while ( config->is_game_running == true )
        {
                start = SDL_GetPerformanceCounter();

                handle_events();

                /* Clear the display */

                set_color( renderer, background );
                SDL_RenderClear( renderer );
                
                /* 
                        All process drawing
                */

                draw_all_components();

                /* Render the display */

                SDL_RenderPresent( renderer );

                /* Game Logic */

                winner = get_winner( config->game );
                if ( config->is_game_ongoing )
                {
                        if ( winner != ' ' || num_vacant_cells( config->game->board ) == 0 )
                        {
                                update_score( config, winner );
                                disable_board();
                                config->is_game_ongoing = false;

                                printf( "Winner is {%c}!\n", winner );
                                if ( winner == config->playerMarker )
                                {
                                        set_status_message( "Player won!" );
                                }
                                else if ( winner == config->computerMarker )
                                {
                                        set_status_message( "Computer won!" );
                                }
                                else
                                {
                                        set_status_message( "It's a tie!" );
                                }
                        }
                        else
                        {
                                set_status_message( "" );
                        }
                }

                /* Fix the framerate to 60 frames per second */

                end = SDL_GetPerformanceCounter();
                
                delta = ( end - start ) / ( float ) SDL_GetPerformanceFrequency() * 1000.0f;
                
                if ( delta < fps_cap_in_ms )
                {
                        SDL_Delay( fps_cap_in_ms - delta );
                }
        }

        SDL_DestroyRenderer( renderer );
        SDL_DestroyWindow( window );
        clean_up();

        return 0;
}

