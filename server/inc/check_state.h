#ifndef CHECK_STATE_H
#define CHECK_STATE_H

#include "get_valid_moves.h"
#include "move.h"

void check_king_threat(struct chess *chess);
int check_state(struct chess *chess);
int has_defence(struct chess *chess, uint8_t (*valid_moves)[BOARD_SIZE],
                struct move_log **log);
int king_defence(struct chess *chess, struct move_log **log);
int has_move(uint8_t (*valid_moves)[BOARD_SIZE]);
int is_draw(struct chess *chess);
void clean_valid_moves(uint8_t (*valid_moves)[BOARD_SIZE]);

#endif
