#ifndef __LIB_GLOBAL_H__
#define __LIB_GLOBAL_H__

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "SDL2/SDL.h"

typedef struct
{
        bool                    is_game_running;
} global_t;

global_t* global_init();

#endif /* __LIB_GLOBAL_H__ */
