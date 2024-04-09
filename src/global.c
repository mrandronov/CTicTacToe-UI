
#include "global.h"

global_t*
global_init()
{
        global_t* global = ( global_t* ) malloc( sizeof( global_t ) );

        global->is_game_running = true;

        return global;
}

