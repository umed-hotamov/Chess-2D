#ifndef GLOBAL_H
#define GLOBAL_H

#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOARD_SIZE 8

#define BOARD_NOTATION                                                         \
  "RNBQKBNR/PPPPPPPP/--------/--------/--------/--------/pppppppp/rnbqkbnr"

enum pieces {
  W_PAWN = 'p',
  W_ROOK = 'r',
  W_KNIGHT = 'n',
  W_BISHOP = 'b',
  W_KING = 'k',
  W_QUEEN = 'q',

  B_PAWN = 'P',
  B_ROOK = 'R',
  B_KNIGHT = 'N',
  B_BISHOP = 'B',
  B_KING = 'K',
  B_QUEEN = 'Q',
};

#endif
