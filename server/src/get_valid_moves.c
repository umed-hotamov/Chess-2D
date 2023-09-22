#include "get_valid_moves.h"

void get_valid_black_pawn_moves(char **board, struct track_piece *piece,
                                uint8_t (*valid_moves)[BOARD_SIZE]) {
  if (piece->row_from == 1) {
    if (board[piece->row_from + 1][piece->col_from] == '-')
      valid_moves[piece->row_from + 1][piece->col_from] = 1;
    if (board[piece->row_from + 2][piece->col_from] == '-')
      valid_moves[piece->row_from + 2][piece->col_from] = 1;
  }

  if (piece->row_from != BOARD_SIZE - 1) {
    if (board[piece->row_from + 1][piece->col_from] == '-')
      valid_moves[piece->row_from + 1][piece->col_from] = 1;
    if (piece->col_from != BOARD_SIZE - 1)
      if (board[piece->row_from + 1][piece->col_from + 1] != '-' &&
          islower(board[piece->row_from + 1][piece->col_from + 1]))
        valid_moves[piece->row_from + 1][piece->col_from + 1] = 1;
    if (piece->col_from != 0)
      if (board[piece->row_from + 1][piece->col_from - 1] != '-' &&
          islower(board[piece->row_from + 1][piece->col_from - 1]))
        valid_moves[piece->row_from + 1][piece->col_from - 1] = 1;
  }
}

void get_valid_white_pawn_moves(char **board, struct track_piece *piece,
                                uint8_t (*valid_moves)[BOARD_SIZE]) {
  if (piece->row_from == 6) {
    if (board[piece->row_from - 1][piece->col_from] == '-')
      valid_moves[piece->row_from - 1][piece->col_from] = 1;
    if (board[piece->row_from - 2][piece->col_from] == '-')
      valid_moves[piece->row_from - 2][piece->col_from] = 1;
  }
  if (piece->row_from != 0) {
    if (board[piece->row_from - 1][piece->col_from] == '-')
      valid_moves[piece->row_from - 1][piece->col_from] = 1;
    if (piece->col_from != BOARD_SIZE - 1)
      if (board[piece->row_from - 1][piece->col_from + 1] != '-' &&
          isupper(board[piece->row_from - 1][piece->col_from + 1]))
        valid_moves[piece->row_from - 1][piece->col_from + 1] = 1;
    if (piece->col_from != 0)
      if (board[piece->row_from - 1][piece->col_from - 1] != '-' &&
          isupper(board[piece->row_from - 1][piece->col_from - 1]))
        valid_moves[piece->row_from - 1][piece->col_from - 1] = 1;
  }
}

/* history_list *get_previous_move(history_list *history) { */
/*     history_list *temp = history; */

/*     if (temp->next == NULL) */
/*         return NULL; */

/*     for (; temp->next->next; temp = temp->next) */
/*         ; */

/*     return temp; */
/* } */

/* void get_valid_pawn_capture(char **board, struct track_piece *piece, uint8_t
 * (*valid_moves)[BOARD_SIZE]) { */
/*     if (*history == NULL) */
/*         return; */

/*     history_list *temp = *history; */
/*     history_list *prev = get_previous_move(temp); */

/*     if (prev == NULL) */
/*         return; */
/*     if (tolower(prev->figure_from) != 'p') */
/*         return; */
/*     if (abs(prev->row_to - prev->row_from) != 2) */
/*         return; */

/*     temp = temp->tail; */
/*     if (game->move.white) { */
/*         if (prev->row_from != 6) */
/*             return; */
/*         if (temp->col_from < BOARD_SIZE - 1) */
/*             if (temp->col_from + 1 == prev->col_to) */
/*                 valid_moves[temp->row_from + 1][temp->col_from + 1] = 1; */
/*         if (temp->col_from != 0) */
/*             if (temp->col_from - 1 == prev->col_to) */
/*                 valid_moves[temp->row_from + 1][temp->col_from - 1] = 1; */
/*     } else { */
/*         if (prev->row_from != 1) */
/*             return; */
/*         if (temp->col_from < BOARD_SIZE - 1) */
/*             if (temp->col_from + 1 == prev->col_to) */
/*                 valid_moves[temp->row_from - 1][temp->col_from + 1] = 1; */
/*         if (temp->col_from != 0) */
/*             if (temp->col_from - 1 == prev->col_to) */
/*                 valid_moves[temp->row_from - 1][temp->col_from - 1] = 1; */
/*     } */
/* } */

void get_valid_rook_moves(char **board, struct track_piece *piece,
                          uint8_t (*valid_moves)[BOARD_SIZE]) {
  int up = piece->row_from;
  int right = piece->col_from;
  int down = piece->row_from;
  int left = piece->col_from;
  char move_state =
      islower(board[piece->row_from][piece->col_from]) ? 'w' : 'b';
  if (up != BOARD_SIZE - 1) {
    for (up++; board[up][piece->col_from] == '-' && up < BOARD_SIZE - 1; up++)
      valid_moves[up][piece->col_from] = 1;
    if (up < BOARD_SIZE) {
      valid_moves[up][piece->col_from] = 1;
      if (move_state == 'w' && islower(board[up][piece->col_from]))
        valid_moves[up][piece->col_from] = 0;

      else if (move_state == 'b' && isupper(board[up][piece->col_from]))
        valid_moves[up][piece->col_from] = 0;
    }
  }
  if (down != 0) {
    for (down--; board[down][piece->col_from] == '-' && down != 0; down--)
      valid_moves[down][piece->col_from] = 1;
    if (down >= 0) {
      valid_moves[down][piece->col_from] = 1;
      if (move_state == 'w' && islower(board[down][piece->col_from]))
        valid_moves[down][piece->col_from] = 0;

      else if (move_state == 'b' && isupper(board[down][piece->col_from]))
        valid_moves[down][piece->col_from] = 0;
    }
  }
  if (right != BOARD_SIZE - 1) {
    for (right++;
         board[piece->row_from][right] == '-' && right < BOARD_SIZE - 1;
         right++)
      valid_moves[piece->row_from][right] = 1;

    if (right < BOARD_SIZE) {
      valid_moves[piece->row_from][right] = 1;
      if (move_state == 'w' && islower(board[piece->row_from][right]))
        valid_moves[piece->row_from][right] = 0;

      else if (move_state == 'b' && isupper(board[piece->row_from][right]))
        valid_moves[piece->row_from][right] = 0;
    }
  }
  if (left != 0) {
    for (left--; board[piece->row_from][left] == '-' && left != 0; left--)
      valid_moves[piece->row_from][left] = 1;
    if (left >= 0) {
      valid_moves[piece->row_from][left] = 1;
      if (move_state == 'w' && islower(board[piece->row_from][left]))
        valid_moves[piece->row_from][left] = 0;

      else if (move_state == 'b' && isupper(board[piece->row_from][left]))
        valid_moves[piece->row_from][left] = 0;
    }
  }
}

void get_valid_knight_moves(char **board, struct track_piece *piece,
                            uint8_t (*valid_moves)[BOARD_SIZE]) {
  int up = piece->row_from;
  int right = piece->col_from;
  int left = piece->col_from;
  int down = piece->row_from;
  char move_state =
      islower(board[piece->row_from][piece->col_from]) ? 'w' : 'b';

  for (int i = 0; i <= 2 && up <= BOARD_SIZE - 1; i++, up++) {
    if (i == 2) {
      if (right != BOARD_SIZE - 1) {
        right++;
        valid_moves[up][right] = 1;
        if (move_state == 'w' && islower(board[up][right]))
          valid_moves[up][right] = 0;
        else if (move_state == 'b' && isupper(board[up][right]))
          valid_moves[up][right] = 0;
      }
      if (left != 0) {
        left--;
        valid_moves[up][left] = 1;
        if (move_state == 'w' && islower(board[up][left]))
          valid_moves[up][left] = 0;

        else if (move_state == 'b' && isupper(board[up][left]))
          valid_moves[up][left] = 0;
      }
    }
  }
  up = piece->row_from;
  right = piece->col_from;
  down = piece->row_from;
  left = piece->col_from;

  if (up != BOARD_SIZE - 1) {
    up++;
    for (int i = 0; i <= 2 && right <= BOARD_SIZE - 1; i++, right++)
      if (i == 2) {
        valid_moves[up][right] = 1;
        if (move_state == 'w' && islower(board[up][right]))
          valid_moves[up][right] = 0;

        else if (move_state == 'b' && isupper(board[up][right]))
          valid_moves[up][right] = 0;
      }
    for (int i = 0; i <= 2 && left >= 0; i++, left--)
      if (i == 2) {
        valid_moves[up][left] = 1;
        if (move_state == 'w' && islower(board[up][left]))
          valid_moves[up][left] = 0;

        else if (move_state == 'b' && isupper(board[up][left]))
          valid_moves[up][left] = 0;
      }
  }
  right = piece->col_from;
  left = piece->col_from;

  if (down != 0) {
    down--;
    for (int i = 0; i <= 2 && right <= BOARD_SIZE - 1; i++, right++)
      if (i == 2) {
        valid_moves[down][right] = 1;
        if (move_state == 'w' && islower(board[down][right]))
          valid_moves[down][right] = 0;

        else if (move_state == 'b' && isupper(board[down][right]))
          valid_moves[down][right] = 0;
      }
    for (int i = 0; i <= 2 && left >= 0; i++, left--)
      if (i == 2) {
        valid_moves[down][left] = 1;
        if (move_state == 'w' && islower(board[down][left]))
          valid_moves[down][left] = 0;

        else if (move_state == 'b' && isupper(board[down][left]))
          valid_moves[down][left] = 0;
      }
  }
  right = piece->col_from;
  down = piece->row_from;
  left = piece->col_from;

  for (int i = 0; i <= 2 && down >= 0; i++, down--) {
    if (i == 2) {
      if (right != BOARD_SIZE - 1) {
        right++;
        valid_moves[down][right] = 1;
        if (move_state == 'w' && islower(board[down][right]))
          valid_moves[down][right] = 0;

        else if (move_state == 'b' && isupper(board[down][right]))
          valid_moves[down][right] = 0;
      }
      if (left != 0) {
        left--;
        valid_moves[down][left] = 1;
        if (move_state == 'w' && islower(board[down][left]))
          valid_moves[down][left] = 0;

        else if (move_state == 'b' && isupper(board[down][left]))
          valid_moves[down][left] = 0;
      }
    }
  }
}

void get_valid_bishop_moves(char **board, struct track_piece *piece,
                            uint8_t (*valid_moves)[BOARD_SIZE]) {
  int up = piece->row_from;
  int right = piece->col_from;
  int down = piece->row_from;
  int left = piece->col_from;
  char move_state =
      islower(board[piece->row_from][piece->col_from]) ? 'w' : 'b';

  if (up != BOARD_SIZE - 1) {
    if (right != BOARD_SIZE - 1) {
      for (up++, right++; board[up][right] == '-' && up != BOARD_SIZE - 1 &&
                          right != BOARD_SIZE - 1;
           up++, right++)
        valid_moves[up][right] = 1;
      if (up < BOARD_SIZE && right < BOARD_SIZE) {
        valid_moves[up][right] = 1;
        if (move_state == 'w' && islower(board[up][right]))
          valid_moves[up][right] = 0;

        else if (move_state == 'b' && isupper(board[up][right]))
          valid_moves[up][right] = 0;
      }
    }
    up = piece->row_from;
    if (left != 0) {
      for (up++, left--;
           board[up][left] == '-' && up != BOARD_SIZE - 1 && left != 0;
           up++, left--)
        valid_moves[up][left] = 1;
      if (up < BOARD_SIZE && left >= 0) {
        valid_moves[up][left] = 1;
        if (move_state == 'w' && islower(board[up][left]))
          valid_moves[up][left] = 0;

        else if (move_state == 'b' && isupper(board[up][left]))
          valid_moves[up][left] = 0;
      }
    }
  }
  right = piece->col_from;
  left = piece->col_from;
  if (down != 0) {
    if (right != BOARD_SIZE - 1) {
      for (down--, right++;
           board[down][right] == '-' && down != 0 && right != BOARD_SIZE - 1;
           down--, right++)
        valid_moves[down][right] = 1;
      if (down >= 0 && right < BOARD_SIZE) {
        valid_moves[down][right] = 1;
        if (move_state == 'w' && islower(board[down][right]))
          valid_moves[down][right] = 0;

        else if (move_state == 'b' && isupper(board[down][right]))
          valid_moves[down][right] = 0;
      }
    }
    down = piece->row_from;
    if (left != 0) {
      for (down--, left--; board[down][left] == '-' && down != 0 && left != 0;
           down--, left--)
        valid_moves[down][left] = 1;
      if (down >= 0 && left >= 0) {
        valid_moves[down][left] = 1;
        if (move_state == 'w' && islower(board[down][left]))
          valid_moves[down][left] = 0;

        else if (move_state == 'b' && isupper(board[down][left]))
          valid_moves[down][left] = 0;
      }
    }
  }
}

void get_valid_queen_moves(char **board, struct track_piece *piece,
                           uint8_t (*valid_moves)[BOARD_SIZE]) {
  get_valid_rook_moves(board, piece, valid_moves);
  get_valid_bishop_moves(board, piece, valid_moves);
}

void get_valid_king_moves(char **board, struct track_piece *piece,
                          uint8_t (*valid_moves)[BOARD_SIZE]) {
  int up = piece->row_from;
  int right = piece->col_from;
  int down = piece->row_from;
  int left = piece->col_from;
  char move_state =
      islower(board[piece->row_from][piece->col_from]) ? 'w' : 'b';

  if (up != BOARD_SIZE - 1) {
    up++;
    valid_moves[up][piece->col_from] = 1;
    if (right != BOARD_SIZE - 1) {
      right++;
      valid_moves[up][right] = 1;
      if (move_state == 'w' && islower(board[up][right]))
        valid_moves[up][right] = 0;

      else if (move_state == 'b' && isupper(board[up][right]))
        valid_moves[up][right] = 0;
    }
    if (left != 0) {
      left--;
      valid_moves[up][left] = 1;
      if (move_state == 'w' && islower(board[up][left]))
        valid_moves[up][left] = 0;

      else if (move_state == 'b' && isupper(board[up][left]))
        valid_moves[up][left] = 0;
    }
  }
  right = piece->col_from;
  left = piece->col_from;
  if (right != BOARD_SIZE - 1) {
    right++;
    valid_moves[piece->row_from][right] = 1;
    if (move_state == 'w' && islower(board[piece->row_from][right]))
      valid_moves[piece->row_from][right] = 0;

    else if (move_state == 'b' && isupper(board[piece->row_from][right]))
      valid_moves[piece->row_from][right] = 0;
  }
  if (left != 0) {
    left--;
    valid_moves[piece->row_from][left] = 1;
    if (move_state == 'w' && islower(board[piece->row_from][left]))
      valid_moves[piece->row_from][left] = 0;

    else if (move_state == 'b' && isupper(board[piece->row_from][left]))
      valid_moves[piece->row_from][left] = 0;
  }
  right = piece->col_from;
  left = piece->col_from;
  if (down != 0) {
    down--;
    valid_moves[down][piece->col_from] = 1;
    if (move_state == 'w' && islower(board[down][piece->col_from]))
      valid_moves[down][piece->col_from] = 0;

    else if (move_state == 'b' && isupper(board[down][piece->col_from]))
      valid_moves[down][piece->col_from] = 0;

    if (right != BOARD_SIZE - 1) {
      right++;
      valid_moves[down][right] = 1;
      if (move_state == 'w' && islower(board[down][right]))
        valid_moves[down][right] = 0;

      else if (move_state == 'b' && isupper(board[down][right]))
        valid_moves[down][right] = 0;
    }
    if (left != 0) {
      left--;
      valid_moves[down][left] = 1;
      if (move_state == 'w' && islower(board[down][left]))
        valid_moves[down][left] = 0;

      else if (move_state == 'b' && isupper(board[down][left]))
        valid_moves[down][left] = 0;
    }
  }
}
