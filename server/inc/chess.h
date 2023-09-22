#ifndef CHESS_H
#define CHESS_H

#include "chess_config.h"

struct chess {
  struct game_status game_status;
  struct move_status move_status;
  struct track_piece piece;
  char **board;
};

#endif
