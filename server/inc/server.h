#ifndef SERVER_H
#define SERVER_H

#include "chess.h"
#include "global.h"
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define IP "127.0.0.1"
#define PORT "1111"

enum network_errors {
  ERR_GETADDRINFO,
  ERR_SERVER,
  ERR_BIND,
  ERR_LISTEN,
  ERR_ACCEPT,
  ERR_SEND,
  ERR_RECV
};

int send_valid_moves(int new_fd, uint8_t (*valid_moves)[BOARD_SIZE]);
int send_board(int new_fd, char **board);
int read_first_move(int new_fd, struct track_piece *piece);
int read_second_move(int new_fd, struct track_piece *piece);
int init_server(void);
int get_connection(int sockfd);
/* int init_server(void); */
/* int create_game_room(void); */
/* void *game_room(void *arg); */

#endif
