#ifndef CHESS_CONFIG_H
#define CHESS_CONFIG_H

#include "stdint.h"

struct move_status {
  uint8_t white;
  uint8_t black;
};

struct game_status {
  uint8_t check;
  uint8_t checkmate;
  uint8_t draw;
};

struct track_king {
  int32_t w_row;
  int32_t w_col;
  int32_t b_row;
  int32_t b_col;
};

struct track_piece {
  int32_t row_from;
  int32_t col_from;
  int32_t row_to;
  int32_t col_to;
  struct track_king king;
};

#endif
