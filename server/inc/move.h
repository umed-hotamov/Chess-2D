#ifndef MOVE_H
#define MOVE_H

#include "check_state.h"
#include "chess.h"
#include "get_valid_moves.h"
#include "global.h"
#include "move_log.h"

enum { DRAW = 1, CHECK, CHECKMATE };

void move(struct track_piece *piece, char **board);
void reset_move(struct track_piece *piece, struct move_log *log, char **board);
void change_move_state(struct move_status *move_status);
void get_valid_moves(struct chess *chess, uint8_t (*valid_moves)[BOARD_SIZE]);
int check_move(struct chess *chess, uint8_t (*valid_moves)[BOARD_SIZE]);
int handle_move(struct chess *chess, uint8_t (*valid_moves)[BOARD_SIZE],
                struct move_log **log);

#endif
