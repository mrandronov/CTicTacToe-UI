cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

project( TicTacToeUI C)

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/include/ )

set( SOURCES src/main.c 
        src/global.c
        src/color.c
        src/button.c
        src/mouse.c
        src/selector.c
        src/label.c
        src/board_display.c 
        src/error.c
        src/config.c
        src/game/board.c
        src/game/game.c 
        src/game/player.c
)

add_executable( TicTacToeGame ${SOURCES} )

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories( /opt/homebrew/include/ )
link_libraries( /opt/homebrew/lib/ )

target_link_libraries( TicTacToeGame SDL2 SDL2_ttf )

