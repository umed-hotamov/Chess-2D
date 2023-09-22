#include "game.h"

struct chess *chess_init(void) {
  struct chess *chess =
      malloc(sizeof(struct chess) * sizeof(char *) * BOARD_SIZE * BOARD_SIZE);

  if (!chess)
    return NULL;

  chess->board = init_board();
  if (!chess->board) {
    free(chess);
    return NULL;
  }

  chess->move_status.white = 1;
  chess->move_status.black = 0;

  chess->game_status.check = 0;
  chess->game_status.checkmate = 0;
  chess->game_status.draw = 0;

  chess->piece.king.w_row = 7;
  chess->piece.king.w_col = 4;

  chess->piece.king.b_row = 0;
  chess->piece.king.b_col = 4;

  return chess;
}

void free_chess(struct chess *chess) {
  for (size_t i = 0; i < BOARD_SIZE; ++i) {
    free(chess->board[i]);
  }
  free(chess);
}

int main(void) {
  struct chess *chess = chess_init();
  if (!chess)
    return EXIT_FAILURE;

  int sockfd = init_server();
  int player = get_connection(sockfd);
  game_process(chess, player);

  close(sockfd);
  free_chess(chess);

  return EXIT_SUCCESS;
}
