
#include "button.h"
#include "mouse.h"
#include "label.h"
#include "board_display.h"

int             button_index;
button_t**      button_list;

SDL_Renderer*   button_renderer;
config_t*       config;

int
new_game()
{
        printf( "Making a new game!\n" );

        /*
                For now, let's just destroy all game 
                resources and rebuild them.

                This is the only clean way to do it since
                I can't enable/disable certain resources
                dynamically, like labels for example.

                This is definitely gonna cause seg faults.
         */

        board_destroy();
        game_free( config->game );
        
        config->game = game_init( 3, 3, config->playerMarker, config->computerMarker );
        set_status_message( "" );
        board_init( button_renderer, config );

        config->is_game_ongoing = true;

        return 0;
}

int
quit_game()
{
        printf( "Quitting the game!\n" );

        config->is_game_running = false;

        return 0;
}

button_t*
button_list_init( SDL_Renderer* renderer, config_t* game_config )
{
        button_renderer = renderer;
        config = game_config;

        button_index = 0;
        button_list = ( button_t** ) malloc( BUTTON_LIST_SIZE * sizeof( button_t* ) );

        /* int continue_game_x = 375; */
        /* int continue_game_y = 650; */
        /* label_create( renderer, "NEW GAME", continue_game_x + 5, continue_game_y + 10, 35 );  */
        /* button_create( continue_game_x,  */
                        /* continue_game_y,  */
                        /* 180, */
                        /* 50,  */
                        /* &default_color,  */
                        /* &highlight_color,  */
                        /* &orange,  */
                        /* &continue_game ); */

        int new_game_x = 375;
        int new_game_y = 650;
        label_create( renderer, "NEW GAME", new_game_x + 5, new_game_y + 10, 35 ); 
        button_create( new_game_x, 
                        new_game_y, 
                        180,
                        50, 
                        &default_color, 
                        &highlight_color, 
                        &orange, 
                        &new_game );

        int quit_game_x = 375;
        int quit_game_y = 725;
        label_create( renderer, "QUIT", quit_game_x + 5, quit_game_y + 10, 35 );
        button_create( quit_game_x, 
                        quit_game_y, 
                        180,
                        50, 
                        &default_color, 
                        &highlight_color, 
                        &orange, 
                        &quit_game );

        return *button_list;
}

button_t*
button_create( int x,
        int y,
        int w,
        int h,
        SDL_Color* color,
        SDL_Color* highlight,
        SDL_Color* select,
        int (*pressFunc)() )
{
        button_t*       button = ( button_t* ) malloc( sizeof( button_t ) );

        button->box = (SDL_Rect) { .x = x, .y = y, .w = w, .h = h };
        button->color = color;
        button->highlight_color = highlight;
        button->selected_color = select;
        button->is_highlighted = 0;
        button->is_pressed = 0;
        button->pressFunc = pressFunc;

        button_list[ button_index ] = button;
        button_index++;

        return button;
}

void
draw_button( SDL_Renderer* renderer, button_t* button )
{
        if ( button->is_highlighted )
        {
                set_color( renderer, *button->highlight_color );
        }
        else
        {
                set_color( renderer, *button->color );
        }

        if ( button->is_pressed )
        {
                set_color( renderer, *button->selected_color );
        }

        SDL_RenderFillRect( renderer, &button->box );
}

void
button_destroy( button_t* button )
{
        free( button );
}

void
press_buttons()
{
        for ( int i = 0; i < button_index; i++ )
        {
                if ( is_mouse_over( button_list[ i ]->box ) )
                {
                        button_list[ i ]->is_pressed = 1;
                }
        }
}

void
unpress_buttons()
{
        for ( int i = 0; i < button_index; i++ )
        {
                if ( is_mouse_over( button_list[ i ]->box ) )
                {
                        button_list[ i ]->is_pressed = 0;
                }
        }
}

void
handle_button_press()
{
        for ( int i = 0; i < button_index; i++ )
        {
                if ( is_mouse_over( button_list[ i ]->box ) )
                {
                        button_list[ i ]->pressFunc();
                }
        }
}

void
draw_button_list( SDL_Renderer* renderer )
{
        for ( int i = 0; i < button_index; i++ )
        {
                draw_button( renderer, button_list[ i ] );
        }
}

void
highlight_buttons()
{
        for ( int i = 0; i < button_index; i++ )
        {
                if ( is_mouse_over( button_list[ i ]->box ) )
                {
                        button_list[ i ]->is_highlighted = 1;
                }
                else
                {
                        button_list[ i ]->is_highlighted = 0;
                }
        }
}

void
button_list_destroy()
{
        if ( button_index == 0 )
        {
                return;
        }

        for ( int i = 0; i < button_index; i++ )
        {
                button_destroy( button_list[ i ] );
        }
        button_index = 0;
}

