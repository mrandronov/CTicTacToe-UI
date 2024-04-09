
#include "label.h"
#include "error.h"

config_t*       config;
int             label_index;
label_t**       label_list;

int             dynamic_label_index;
label_t**       dynamic_label_list;

const char*     font_path = "./fonts/8bitOperatorPlus8-Regular.ttf";
char*           status_message = "";

int
get_label_index()
{
        return label_index;
}

label_t*
label_default_create( SDL_Renderer* renderer, const char* str, int x, int y, int size )
{
        label_t* label = malloc( sizeof( label_t ) );
        TTF_Font* font = TTF_OpenFont( font_path, size );
        assert_msg( (font == NULL), TTF_GetError() );

        SDL_Surface* surface = TTF_RenderText_Solid(font, str, white);
        assert_msg( (surface == NULL), TTF_GetError() );

        label->texture = SDL_CreateTextureFromSurface( renderer, surface );
        assert_msg( (label->texture == NULL), SDL_GetError() );

        label->rect.x = x;
        label->rect.y = y;

        assert_msg( ( SDL_QueryTexture( label->texture,
                                        NULL,
                                        NULL,
                                        &( label->rect.w ), 
                                        &( label->rect.h ) ) != 0 ),
                        SDL_GetError() );

        SDL_FreeSurface( surface );
        TTF_CloseFont( font );

        return label;
}

label_t*
label_create( SDL_Renderer* renderer, const char* str, int x, int y, int size )
{
        label_t*        label = label_default_create( renderer, str, x, y, size );

        label_list[ label_index ] = label;
        label_index++;

        return label;
}


label_t*
dynamic_label_create( SDL_Renderer* renderer, const char* str, int x, int y, int size ) 
{
        label_t*        label = label_default_create( renderer, str, x, y, size );

        dynamic_label_list[ dynamic_label_index ] = label;
        dynamic_label_index++;

        return label;
}

void
label_draw( SDL_Renderer* renderer, label_t* label )
{
        SDL_RenderCopy( renderer, label->texture, NULL, &label->rect );
}

void
label_destroy( label_t* label )
{
        if ( label == NULL )
        {
                return;
        }

        if ( label->texture )
        {
                SDL_DestroyTexture( label->texture );
        }

        free( label );
}

label_t**
label_list_init( SDL_Renderer* renderer, config_t* game_config )
{
        config = game_config;
        label_index = 0;
        label_list = ( label_t** ) malloc( LABEL_LIST_SIZE * sizeof( label_t ) );

        label_create( renderer, "Choose a marker: ", 50, 570, 25 );
        label_create( renderer, "Choose an AI style: ", 50, 700, 25 );

        return label_list;
}

void
draw_label_list( SDL_Renderer* renderer )
{
        for ( int i = 0; i < label_index; i++ )
        {
                label_draw( renderer, label_list[ i ] );
        }
}

void
label_list_destroy_from_index( int start_index )
{
        for ( int i = start_index; i < label_index; i++ )
        {
                label_destroy( label_list[ i ] );
        }
        label_index -= ( label_index - start_index );
}

void
label_list_destroy()
{
        if ( label_index == 0 )
        {
                return;
        }

        for ( int i = 0; i < label_index; i++ )
        {
                label_destroy( label_list[ i ] );
        }
        label_index = 0;
}

void
reset_player_score()
{
        config->playerScore = 0;
}

void
reset_computer_score()
{
        config->computerScore = 0;
}

void
set_status_message( char* msg )
{
        status_message = msg;
}

/*
        Dynamic text needs to be re-rendered and destroyed
        every single frame in order to appear 'dynamic'.

        These are used for score counts and pop up messages.
 */

label_t**
dynamic_labels_list_init()
{
        dynamic_label_index = 0;
        dynamic_label_list = ( label_t** ) malloc( DYNAMIC_LABEL_LIST_SIZE * sizeof( label_t* ) );

        return dynamic_label_list;
}

void
dynamic_labels_destroy()
{
        if ( dynamic_label_index == 0 )
        {
                return;
        }
        
        for ( int i = 0; i < dynamic_label_index; i++ )
        {
                label_destroy( dynamic_label_list[ i ] );
        }

        dynamic_label_index = 0;
}

void
draw_dynamic_labels( SDL_Renderer* renderer )
{
        dynamic_labels_destroy();

        char    playerBuf[ 1024 ];
        sprintf( playerBuf, "Player: %d", config->playerScore );
        dynamic_label_create( renderer, playerBuf, 375, 570, 25 ); 

        char    computerBuf[ 1024 ];
        sprintf( computerBuf, "Computer: %d", config->computerScore );
        dynamic_label_create( renderer, computerBuf, 375, 600, 25 ); 

        if ( strcmp( status_message, "" ) != 0 )
        {
                dynamic_label_create( renderer, status_message, 200, 540, 20 ); 
        }

        for( int i = 0; i < dynamic_label_index; i++ )
        {
                label_draw( renderer, dynamic_label_list[ i ] );
        }
}

