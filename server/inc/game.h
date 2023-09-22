#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "check_state.h"
#include "chess.h"
#include "move.h"
#include "server.h"

void *game_process(struct chess *chess, int sockfd);

#endif
