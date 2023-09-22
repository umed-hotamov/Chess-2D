#ifndef MOVE_LOG_H
#define MOVE_LOH_H

#include "chess.h"
#include "global.h"

struct move_log {
  size_t row_from;
  size_t col_from;
  size_t row_to;
  size_t col_to;
  char piece_from;
  char piece_to;
  struct move_log *next;
  struct move_log *tail;
};

int add(struct move_log **move_log, struct chess *chess);
int pop(struct move_log **move_log);
void free_log(struct move_log *log);

#endif
