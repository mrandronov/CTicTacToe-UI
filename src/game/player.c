
#include "game/player.h"
#include "game/game.h"

player_t*
init_player( char* name, 
                char piece, 
                move_t* moveFunc( board_t*, char, char ) )
{
        player_t*       player = ( player_t* ) malloc( sizeof( player_t ) );

        player->name = name;
        player->piece = piece;

        player->makeMove = moveFunc; 

        return player;
}

player_t*
init_human_player( char playerPiece )
{
        return init_player( "Human", playerPiece, &get_player_move );
}

player_t*
init_computer_player( char computerPiece )
{
        return init_player( "Computer", computerPiece, &get_computer_move );
}

move_t*
get_player_move( board_t* board, char playerPiece, char computerPiece )
{
        size_t                  bufferSize = 64;
        char*                   inputBuffer = ( char* ) malloc( bufferSize * sizeof( char ) );

        printf( "Please enter the row and column to mark a piece: " );

        getline( &inputBuffer, &bufferSize, stdin );

        move_t*         move = ( move_t* ) malloc( sizeof( move_t ) );
        char*           token = strtok( inputBuffer, " " );

        move->row = atoi( token );

        token = strtok( NULL, " " );

        move->col = atoi( token );

        move->piece = playerPiece;

        free( inputBuffer );

        return move;
}

/*
        TODO: Implement Alpha-Beta pruning technique to
        determine computer move.
 */

int
minimax( int alpha, int beta, board_t* board, char computerPiece, char playerPiece, bool maximizingPlayer )
{
        if ( find_winner( board, computerPiece, playerPiece ) == computerPiece )
        {
                return 1 * ( 1 + num_vacant_cells( board ) );
        }
        else if ( find_winner( board, computerPiece, playerPiece ) == playerPiece )
        {
                return -1 * ( -1 + num_vacant_cells( board ) );
        }
        else
        {
                if ( num_vacant_cells( board ) == 0 )
                {
                        return 0;
                }
        }

        if ( maximizingPlayer )
        {
                int             maxEval = INT_MIN;
                for ( int i = 0; i < board->rows; i++ )
                {
                        for ( int j = 0; j < board->cols; j++ )
                        {
                                if ( board->cells[ i ][ j ].piece == ' ' )
                                {
                                        /*
                                                Get the potential score from here.
                                         */

                                        board->cells[ i ][ j ].piece = computerPiece;

                                        int     eval = minimax( alpha,
                                                        beta,
                                                        board, 
                                                        computerPiece,
                                                        playerPiece,
                                                        false );

                                        board->cells[ i ][ j ].piece = ' ';

                                        maxEval = ( eval > maxEval ) ? eval : maxEval;

                                        if ( maxEval >= beta )
                                        {
                                                return maxEval;
                                        }

                                        alpha = ( eval > alpha ) ? eval : alpha;
                                }
                        }
                }
                return maxEval;
        }
        else
        {
                int             minEval = INT_MAX;
                for ( int i = 0; i < board->rows; i++ )
                {
                        for ( int j = 0; j < board->cols; j++ )
                        {
                                if ( board->cells[ i ][ j ].piece == ' ' )
                                {
                                        /*
                                                Get the potential score from here.
                                         */
                                        
                                        board->cells[ i ][ j ].piece = playerPiece;

                                        int     eval = minimax( alpha,
                                                        beta,
                                                        board, 
                                                        computerPiece,
                                                        playerPiece,
                                                        true );
                                        
                                        board->cells[ i ][ j ].piece = ' ';

                                        minEval = ( eval < minEval ) ? eval : minEval;

                                        if ( minEval <= alpha )
                                        {
                                                return minEval;
                                        }

                                        beta = ( eval < beta ) ? eval : beta;
                                }
                        }
                }
                return minEval;
        }

        return 0;
}

move_t*
get_computer_move( board_t* board, char computerPiece, char playerPiece )
{
        int                     maxScore = INT_MIN;
        move_t*                 move = ( move_t* ) malloc( sizeof( move_t ) );

        move->piece = computerPiece;

        printf( "Computer is thinking... " );

        for ( int i = 0; i < board->rows; i++ )
        {
                for ( int j = 0; j < board->cols; j++ )
                {
                        if ( board->cells[ i ][ j ].piece == ' ' )
                        {
                                board->cells[ i ][ j ].piece = computerPiece;

                                int                    score = minimax( INT_MIN,
                                                                INT_MAX,
                                                                board, 
                                                                computerPiece,
                                                                playerPiece,
                                                                true );
                                board->cells[ i ][ j ].piece = ' ';

                                if ( score > maxScore )
                                {
                                        maxScore = score;
                                        move->row = i+1;
                                        move->col = j+1;
                                }
                        }
                }
        }

        printf( "Computer marks cell (%d %d) with %c!\n", move->row, move->col, move->piece );

        return move;
}

