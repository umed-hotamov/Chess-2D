#include "move_log.h"

int add(struct move_log **log, struct chess *chess) {
  struct move_log *new_log = malloc(sizeof(struct move_log));
  if (!new_log)
    return 1;

  new_log->row_from = chess->piece.row_from;
  new_log->col_from = chess->piece.col_from;
  new_log->row_to = chess->piece.row_to;
  new_log->col_to = chess->piece.col_to;

  new_log->piece_from =
      chess->board[chess->piece.row_from][chess->piece.col_from];
  new_log->piece_to = chess->board[chess->piece.row_to][chess->piece.col_to];

  new_log->next = NULL;

  if (*log == NULL) {
    *log = new_log;
    (*log)->tail = *log;
  } else {
    (*log)->tail = (*log)->tail->next = new_log;
  }

  return 0;
}

int pop(struct move_log **log) {
  struct move_log *temp = *log;

  if (temp == NULL)
    return 1;

  if (temp->next == NULL) {
    free(temp);
    *log = NULL;
  } else {
    for (; temp->next->next; temp = temp->next)
      ;
    temp->tail = temp;
    free(temp->next);
    temp->next = NULL;
    (*log)->tail = temp;
  }

  return 0;
}

void free_log(struct move_log *log) {
  struct move_log *next;
  for (; log; log = next) {
    next = log->next;
    free(log);
  }
}
