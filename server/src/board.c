#include "global.h"

void print_board(char **board) {
  printf("\n");
  for (size_t rank = 0; rank < BOARD_SIZE; ++rank) {
    for (size_t file = 0; file < BOARD_SIZE; ++file) {
      printf("%c  ", board[rank][file]);
    }
    printf("\n");
  }
  printf("\n");
}

char **init_board(void) {
  char **board = malloc(sizeof(char *) * BOARD_SIZE);
  if (board == NULL)
    return NULL;

  for (size_t i = 0; i < BOARD_SIZE; i++) {
    board[i] = malloc(BOARD_SIZE);
    if (board[i] == NULL)
      return NULL;
  }
  size_t rank = 0, file = 0;
  for (size_t i = 0; BOARD_NOTATION[i] != '\0'; i++) {
    if (BOARD_NOTATION[i] == '/') {
      i++;
      rank++;
      file = 0;
    }
    board[rank][file] = BOARD_NOTATION[i];
    file++;
  }

  return board;
}

void reverse_board(char **board) {
  for (size_t i = 0; i < BOARD_SIZE / 2; ++i) {
    char *temp = board[BOARD_SIZE - i - 1];
    board[BOARD_SIZE - i - 1] = board[i];
    board[i] = temp;
  }
}
