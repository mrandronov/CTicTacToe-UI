
#include "config.h"
#include "game/board.h"

config_t*
config_init()
{
        config_t*       config = ( config_t* ) malloc( sizeof( config_t ) );

        config->playerMarker = 'O';
        config->computerMarker = 'X';
        config->computerType = SMART;
        config->playerScore = 0;
        config->computerScore = 0;
        config->is_game_ongoing = true;
        config->is_game_running = true;

        config->game = game_init( 3, 3, config->playerMarker, config->computerMarker, config->computerType ); 

        return config;
}

void
update_score( config_t* config, char winner )
{
        if ( winner == config->playerMarker )
        {
                config->playerScore++;
        }
        else if ( winner == config->computerMarker )
        {
                config->computerScore++;
        }

        /*
                else, we got a tie!
         */
}

