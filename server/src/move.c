#include "move.h"
#include "board.h"

void get_valid_moves(struct chess *chess, uint8_t (*valid_moves)[BOARD_SIZE]) {
  switch (chess->board[chess->piece.row_from][chess->piece.col_from]) {
  case B_ROOK:
  case W_ROOK:
    get_valid_rook_moves(chess->board, &chess->piece, valid_moves);
    break;
  case B_KNIGHT:
  case W_KNIGHT:
    get_valid_knight_moves(chess->board, &chess->piece, valid_moves);
    break;
  case W_BISHOP:
  case B_BISHOP:
    get_valid_bishop_moves(chess->board, &chess->piece, valid_moves);
    break;
  case B_QUEEN:
  case W_QUEEN:
    get_valid_queen_moves(chess->board, &chess->piece, valid_moves);
    break;
  case B_KING:
  case W_KING:
    get_valid_king_moves(chess->board, &chess->piece, valid_moves);
    break;
  case W_PAWN:
    get_valid_white_pawn_moves(chess->board, &chess->piece, valid_moves);
    break;
  case B_PAWN:
    get_valid_black_pawn_moves(chess->board, &chess->piece, valid_moves);
    break;
  }
}

void change_move_state(struct move_status *move_status) {
  if (move_status->white) {
    move_status->white = 0;
    move_status->black = 1;
  } else {
    move_status->black = 0;
    move_status->white = 1;
  }
}

int check_premove(struct chess *chess, uint8_t (*valid_moves)[BOARD_SIZE]) {
  size_t row_from = chess->piece.row_from;
  size_t col_from = chess->piece.col_from;

  if (chess->move_status.black && !isupper(chess->board[row_from][col_from]))
    return 1;
  if (chess->move_status.white && !islower(chess->board[row_from][col_from]))
    return 1;

  size_t row_to = chess->piece.row_to;
  size_t col_to = chess->piece.col_to;

  if (!valid_moves[row_to][col_to])
    return 1;

  return 0;
}

void move(struct track_piece *piece, char **board) {
  if (board[piece->row_from][piece->col_from] == W_KING) {
    piece->king.w_row = piece->row_to;
    piece->king.w_col = piece->col_to;
  }
  if (board[piece->row_from][piece->col_from] == B_KING) {
    piece->king.b_row = piece->row_to;
    piece->king.b_col = piece->col_to;
  }
  board[piece->row_to][piece->col_to] = board[piece->row_from][piece->col_from];
  board[piece->row_from][piece->col_from] = '-';
}

void reset_move(struct track_piece *piece, struct move_log *log, char **board) {
  if (board[piece->row_to][piece->col_to] == W_KING) {
    piece->king.w_row = piece->row_from;
    piece->king.w_col = piece->col_from;
  }
  if (board[piece->row_to][piece->col_to] == B_KING) {
    piece->king.b_row = piece->row_from;
    piece->king.b_col = piece->col_from;
  }

  board[piece->row_from][piece->col_from] = log->tail->piece_from;
  board[piece->row_to][piece->col_to] = log->tail->piece_to;
}

int handle_move(struct chess *chess, uint8_t (*valid_moves)[BOARD_SIZE],
                struct move_log **log) {
  int err = check_premove(chess, valid_moves);
  if (err) {
    pop(log);
    return err;
  }

  move(&chess->piece, chess->board);

  err = is_draw(chess);
  if (err) {
    chess->game_status.draw = 1;
    return DRAW;
  }
  err = check_state(chess);
  if (err) {
    reset_move(&chess->piece, *log, chess->board);
    pop(log);
    return err;
  }
  change_move_state(&chess->move_status);

  err = check_state(chess);
  if (err) {
    err = king_defence(chess, log);
    if (err) {
      chess->game_status.checkmate = 1;
      return CHECKMATE;
    }

    return 0;
  }

  return 0;
}
