#include "check_state.h"

void clean_valid_moves(uint8_t (*valid_moves)[BOARD_SIZE]) {
  memset(valid_moves, 0, BOARD_SIZE * BOARD_SIZE);
}

void check_king_threat(struct chess *chess) {
  uint8_t valid_moves[BOARD_SIZE][BOARD_SIZE] = {{0}};
  int temp_row_from = chess->piece.row_from;
  int temp_col_from = chess->piece.col_from;

  if (chess->move_status.white) {
    for (size_t i = 0; i < BOARD_SIZE; ++i) {
      for (size_t j = 0; j < BOARD_SIZE; ++j) {
        switch (chess->board[i][j]) {
        case B_ROOK:
          chess->piece.row_from = i;
          chess->piece.col_from = j;
          get_valid_rook_moves(chess->board, &chess->piece, valid_moves);
          break;
        case B_KNIGHT:
          chess->piece.row_from = i;
          chess->piece.col_from = j;
          get_valid_knight_moves(chess->board, &chess->piece, valid_moves);
          break;
        case B_BISHOP:
          chess->piece.row_from = i;
          chess->piece.col_from = j;
          get_valid_bishop_moves(chess->board, &chess->piece, valid_moves);
          break;
        case B_QUEEN:
          chess->piece.row_from = i;
          chess->piece.col_from = j;
          get_valid_queen_moves(chess->board, &chess->piece, valid_moves);
          break;
        case B_PAWN:
          chess->piece.row_from = i;
          chess->piece.col_from = j;
          get_valid_black_pawn_moves(chess->board, &chess->piece, valid_moves);
          break;
        }
      }
    }
    if (valid_moves[chess->piece.king.w_row][chess->piece.king.w_col]) {
      chess->game_status.check = 1;
      chess->piece.row_from = temp_row_from;
      chess->piece.col_from = temp_col_from;
      return;
    }
    chess->game_status.check = 0;
    chess->piece.row_from = temp_row_from;
    chess->piece.col_from = temp_col_from;

  } else if (chess->move_status.black) {
    for (size_t i = 0; i < BOARD_SIZE; ++i) {
      for (size_t j = 0; j < BOARD_SIZE; ++j) {
        switch (chess->board[i][j]) {
        case W_ROOK:
          chess->piece.row_from = i;
          chess->piece.col_from = j;
          get_valid_rook_moves(chess->board, &chess->piece, valid_moves);
          break;
        case W_KNIGHT:
          chess->piece.row_from = i;
          chess->piece.col_from = j;
          get_valid_knight_moves(chess->board, &chess->piece, valid_moves);
          break;
        case W_BISHOP:
          chess->piece.row_from = i;
          chess->piece.col_from = j;
          get_valid_bishop_moves(chess->board, &chess->piece, valid_moves);
          break;
        case W_QUEEN:
          chess->piece.row_from = i;
          chess->piece.col_from = j;
          get_valid_queen_moves(chess->board, &chess->piece, valid_moves);
          break;
        case W_PAWN:
          chess->piece.row_from = i;
          chess->piece.col_from = j;
          get_valid_white_pawn_moves(chess->board, &chess->piece, valid_moves);
          break;
        }
      }
    }
    if (valid_moves[chess->piece.king.b_row][chess->piece.king.b_col]) {
      chess->game_status.check = 1;
      chess->piece.row_from = temp_row_from;
      chess->piece.col_from = temp_col_from;
      return;
    }
    chess->game_status.check = 0;
    chess->piece.row_from = temp_row_from;
    chess->piece.col_from = temp_col_from;
  }
}

int check_state(struct chess *chess) {
  check_king_threat(chess);
  return chess->game_status.check;
}

int has_defence(struct chess *chess, uint8_t (*valid_moves)[BOARD_SIZE],
                struct move_log **log) {
  int err;
  if (chess->move_status.white) {
    for (size_t i = 0; i < BOARD_SIZE; i++) {
      for (size_t j = 0; j < BOARD_SIZE; j++) {
        if (valid_moves[i][j]) {
          chess->piece.row_to = i;
          chess->piece.col_to = j;
          add(log, chess);
          move(&chess->piece, chess->board);
          err = check_state(chess);
          reset_move(&chess->piece, *log, chess->board);
          pop(log);
          if (!err)
            return 0;
        }
      }
    }

  } else if (chess->move_status.black) {
    for (size_t i = 0; i < BOARD_SIZE; i++) {
      for (size_t j = 0; j < BOARD_SIZE; j++) {
        if (valid_moves[i][j]) {
          chess->piece.row_to = i;
          chess->piece.col_to = j;
          add(log, chess);
          move(&chess->piece, chess->board);
          err = check_state(chess);
          reset_move(&chess->piece, *log, chess->board);
          pop(log);
          if (!err)
            return 0;
        }
      }
    }
  }

  return 1;
}

int king_defence(struct chess *chess, struct move_log **log) {
  uint8_t valid_moves[BOARD_SIZE][BOARD_SIZE] = {{0}};
  int def_rook;
  int def_pawn;
  int def_bishop;
  int def_queen;
  int def_knight;
  int def_king;
  if (chess->move_status.white) {
    for (size_t i = 0; i < BOARD_SIZE; ++i) {
      for (size_t j = 0; j < BOARD_SIZE; ++j) {
        switch (chess->board[i][j]) {
        case W_ROOK:
          chess->piece.row_from = i;
          chess->piece.col_from = j;
          get_valid_rook_moves(chess->board, &chess->piece, valid_moves);
          def_rook = has_defence(chess, valid_moves, log);
          clean_valid_moves(valid_moves);
          if (!def_rook)
            return 0;
          break;
        case W_KNIGHT:
          chess->piece.row_from = i;
          chess->piece.col_from = j;
          get_valid_knight_moves(chess->board, &chess->piece, valid_moves);
          def_knight = has_defence(chess, valid_moves, log);
          clean_valid_moves(valid_moves);
          if (!def_knight)
            return 0;
          break;
        case W_BISHOP:
          chess->piece.row_from = i;
          chess->piece.col_from = j;
          get_valid_bishop_moves(chess->board, &chess->piece, valid_moves);
          def_bishop = has_defence(chess, valid_moves, log);
          clean_valid_moves(valid_moves);
          if (!def_bishop)
            return 0;
          break;
        case W_QUEEN:
          chess->piece.row_from = i;
          chess->piece.col_from = j;
          get_valid_queen_moves(chess->board, &chess->piece, valid_moves);
          def_queen = has_defence(chess, valid_moves, log);
          clean_valid_moves(valid_moves);
          if (!def_queen)
            return 0;
          break;
        case W_PAWN:
          chess->piece.row_from = i;
          chess->piece.col_from = j;
          get_valid_white_pawn_moves(chess->board, &chess->piece, valid_moves);
          def_pawn = has_defence(chess, valid_moves, log);
          clean_valid_moves(valid_moves);
          if (!def_pawn)
            return 0;
          break;
        case W_KING:
          chess->piece.row_from = i;
          chess->piece.col_from = j;
          get_valid_king_moves(chess->board, &chess->piece, valid_moves);
          def_king = has_defence(chess, valid_moves, log);
          clean_valid_moves(valid_moves);
          if (!def_king)
            return 0;
        }
      }
    }
  } else if (chess->move_status.black) {
    for (size_t i = 0; i < BOARD_SIZE; ++i) {
      for (size_t j = 0; j < BOARD_SIZE; ++j) {
        switch (chess->board[i][j]) {
        case B_ROOK:
          chess->piece.row_from = i;
          chess->piece.col_from = j;
          get_valid_rook_moves(chess->board, &chess->piece, valid_moves);
          def_rook = has_defence(chess, valid_moves, log);
          clean_valid_moves(valid_moves);
          if (!def_rook)
            return 0;
          break;
        case B_KNIGHT:
          chess->piece.row_from = i;
          chess->piece.col_from = j;
          get_valid_knight_moves(chess->board, &chess->piece, valid_moves);
          def_knight = has_defence(chess, valid_moves, log);
          clean_valid_moves(valid_moves);
          if (!def_knight)
            return 0;
          break;
        case B_BISHOP:
          chess->piece.row_from = i;
          chess->piece.col_from = j;
          get_valid_bishop_moves(chess->board, &chess->piece, valid_moves);
          def_bishop = has_defence(chess, valid_moves, log);
          clean_valid_moves(valid_moves);
          if (!def_bishop)
            return 0;
          break;
        case B_QUEEN:
          chess->piece.row_from = i;
          chess->piece.col_from = j;
          get_valid_queen_moves(chess->board, &chess->piece, valid_moves);
          def_queen = has_defence(chess, valid_moves, log);
          clean_valid_moves(valid_moves);
          if (!def_queen)
            return 0;
          break;
        case B_PAWN:
          chess->piece.row_from = i;
          chess->piece.col_from = j;
          get_valid_black_pawn_moves(chess->board, &chess->piece, valid_moves);
          def_pawn = has_defence(chess, valid_moves, log);
          clean_valid_moves(valid_moves);
          if (!def_pawn)
            return 0;
          break;
        case B_KING:
          chess->piece.row_from = i;
          chess->piece.col_from = j;
          get_valid_king_moves(chess->board, &chess->piece, valid_moves);
          def_king = has_defence(chess, valid_moves, log);
          clean_valid_moves(valid_moves);
          if (!def_king)
            return 0;
        }
      }
    }
  }

  return 1;
}

int has_move(uint8_t (*valid_moves)[BOARD_SIZE]) {
  for (size_t i = 0; i < BOARD_SIZE; i++) {
    for (size_t j = 0; j < BOARD_SIZE; j++) {
      if (valid_moves[i][j])
        return 0;
    }
  }

  return 1;
}

int is_draw(struct chess *chess) {
  uint8_t valid_moves[BOARD_SIZE][BOARD_SIZE] = {{0}};
  int is_move;
  if (chess->move_status.white) {
    for (size_t i = 0; i < BOARD_SIZE; i++) {
      for (size_t j = 0; j < BOARD_SIZE; j++) {
        switch (chess->board[i][j]) {
        case W_PAWN:
          get_valid_white_pawn_moves(chess->board, &chess->piece, valid_moves);
          is_move = has_move(valid_moves);
          clean_valid_moves(valid_moves);
          if (!is_move)
            return 0;
          break;
        case W_KING:
          get_valid_king_moves(chess->board, &chess->piece, valid_moves);
          is_move = has_move(valid_moves);
          clean_valid_moves(valid_moves);
          if (!is_move)
            return 0;
        }
      }
    }

  } else if (chess->move_status.black) {
    for (size_t i = 0; i < BOARD_SIZE; i++) {
      for (size_t j = 0; j < BOARD_SIZE; j++) {
        switch (chess->board[i][j]) {
        case B_PAWN:
          get_valid_black_pawn_moves(chess->board, &chess->piece, valid_moves);
          is_move = has_move(valid_moves);
          clean_valid_moves(valid_moves);
          if (!is_move)
            return 0;
          break;
        case B_KING:
          get_valid_king_moves(chess->board, &chess->piece, valid_moves);
          is_move = has_move(valid_moves);
          clean_valid_moves(valid_moves);
          if (!is_move)
            return 0;
        }
      }
    }
  }

  return 1;
}
