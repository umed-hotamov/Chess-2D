#ifndef GET_VALID_MOVES_H
#define GET_VALID_MOVES_H

#include "chess.h"
#include "global.h"

void get_valid_white_pawn_moves(char **board, struct track_piece *piece,
                                uint8_t (*valid_moves)[BOARD_SIZE]);

void get_valid_black_pawn_moves(char **board, struct track_piece *piece,
                                uint8_t (*valid_moves)[BOARD_SIZE]);

void get_valid_rook_moves(char **board, struct track_piece *piece,
                          uint8_t (*valid_moves)[BOARD_SIZE]);

void get_valid_knight_moves(char **board, struct track_piece *piece,
                            uint8_t (*valid_moves)[BOARD_SIZE]);

void get_valid_bishop_moves(char **board, struct track_piece *piece,
                            uint8_t (*valid_moves)[BOARD_SIZE]);

void get_valid_queen_moves(char **board, struct track_piece *piece,
                           uint8_t (*valid_moves)[BOARD_SIZE]);

void get_valid_king_moves(char **board, struct track_piece *square,
                          uint8_t (*valid_moves)[BOARD_SIZE]);
/* void get_valid_pawn_capture(Game *game, history_list **history, */
/*                                uint8_t valid_moves[BOARD_SIZE]); */
/* history_list *get_previous_move(history_list *history); */

#endif
