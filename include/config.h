#ifndef __LIB_CONFIG_H__
#define __LIB_CONFIG_H__

#include <stdio.h>
#include <stdlib.h>

#include "game/game.h"

enum computer_type_t
{
        RANDOM,
        SMART
};

typedef struct
{
        char                    playerMarker;
        char                    computerMarker;
        enum computer_type_t    computerType;
        int                     playerScore;
        int                     computerScore;
        bool                    is_game_ongoing;
        bool                    is_game_running;
        game_t*                 game;
} config_t;

config_t* config_init();

void update_score( config_t* conig, char winner );

#endif /* __LIB_CONFIG_H__*/
