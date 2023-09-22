#include "game.h"

/* struct game_room { */
/*     int main_player; */
/*     int rival; */
/*     int wait_for_opponent; */
/*     struct chess *chess; */
/* }; */

/* pthread_cond_t cond; */
/* pthread_mutex_t mutex; */

int send_valid_moves(int new_fd, uint8_t (*valid_moves)[BOARD_SIZE]) {
  char buffer[1024];
  size_t buff_size = 0;
  for (size_t i = 0; i < BOARD_SIZE; ++i) {
    for (size_t j = 0; j < BOARD_SIZE; ++j)
      buffer[buff_size++] = valid_moves[i][j] + '0';
  }
  buffer[buff_size] = '\0';

  if (send(new_fd, buffer, strlen(buffer), 0) == -1) {
    perror("send");
    exit(ERR_SEND);
  }

  return 0;
}

int send_board(int new_fd, char **board) {
  char buffer[1024];
  size_t buff_size = 0;
  for (size_t i = 0; i < BOARD_SIZE; ++i) {
    for (size_t j = 0; j < BOARD_SIZE; ++j)
      buffer[buff_size++] = board[i][j];
    buffer[buff_size++] = '/';
  }
  buffer[buff_size - 1] = '\0';

  if (send(new_fd, buffer, strlen(buffer), 0) == -1) {
    perror("send");
    exit(ERR_SEND);
  }

  return 0;
}

int read_first_move(int new_fd, struct track_piece *piece) {
  char buffer[10];
  memset(buffer, 0, sizeof(buffer));
  if (recv(new_fd, buffer, 10, 0) == -1) {
    perror("recv");
    exit(ERR_RECV);
  }

  piece->row_from = buffer[0] - '0';
  piece->col_from = buffer[1] - '0';

  return 0;
}

int read_second_move(int new_fd, struct track_piece *piece) {
  char buffer[10];
  memset(buffer, 0, sizeof(buffer));
  if (recv(new_fd, buffer, 10, 0) == -1) {
    perror("recv");
    exit(ERR_RECV);
  }

  piece->row_to = buffer[0] - '0';
  piece->col_to = buffer[1] - '0';

  return 0;
}

int init_server(void) {
  int sockfd;
  struct addrinfo hints, *servinfo;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  int status = getaddrinfo(IP, PORT, &hints, &servinfo);
  if (status) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
    exit(ERR_GETADDRINFO);
  }

  if ((sockfd = socket(servinfo->ai_family, servinfo->ai_socktype,
                       servinfo->ai_protocol)) == -1) {
    perror("server: error");
    exit(ERR_SERVER);
  }
  if (bind(sockfd, servinfo->ai_addr, servinfo->ai_addrlen) == -1) {
    close(sockfd);
    perror("bind: error");
    exit(ERR_BIND);
  }

  freeaddrinfo(servinfo);

  return sockfd;
}

int get_connection(int sockfd) {
  struct addrinfo hints, *servinfo;
  struct sockaddr_storage con_addr;
  socklen_t sin_size;

  if (listen(sockfd, 10) == -1) {
    perror("listen");
    exit(ERR_LISTEN);
  }

  int new_fd = accept(sockfd, (struct sockaddr *)&con_addr, &sin_size);
  if (new_fd == 1) {
    perror("accept");
    exit(ERR_ACCEPT);
  }
  
  return new_fd;
}

void *game_process(struct chess *chess, int player) {
  struct move_log *log = NULL;
  uint8_t valid_moves[BOARD_SIZE][BOARD_SIZE] = {{0}};
  int status = 0;
  do {
    read_first_move(player, &chess->piece);
    get_valid_moves(chess, valid_moves);
    send_valid_moves(player, valid_moves);
    read_second_move(player, &chess->piece);
    add(&log, chess);
    status = handle_move(chess, valid_moves, &log);
    send_board(player, chess->board);
    clean_valid_moves(valid_moves);

  } while (!chess->game_status.checkmate);

  return 0;
}

/* void *game_room(void *arg) { */
/*     struct game_room *room = arg; */
/*     char white = 'w'; */
/*     char black = 'b'; */
/*     room->wait_for_opponent = 1; */

/*     pthread_mutex_lock(&mutex); */
/*     pthread_cond_wait(&cond, &mutex); */
/*     room->wait_for_opponent = 0; */
/*     pthread_mutex_unlock(&mutex); */

/*     send(room->main_player, &white, sizeof(white), 0); */
/*     send(room->rival, &black, sizeof(black), 0); */

/*     pthread_t tid[1]; */

/*     pthread_create(&tid[0], NULL, game_process, room); */
/*     /1* pthread_mutex_lock(&mutex); *1/ */
/*     /1* printf("here - %d\n", room->main_player); *1/ */
/*     /1* printf("here - %d\n", room->rival); *1/ */
/*     int temp = room->main_player; */
/*     room->main_player = room->rival; */
/*     room->rival = temp; */
/*     /1* pthread_mutex_unlock(&mutex); *1/ */
/*     pthread_create(&tid[1], NULL, game_process, room); */

/*     return 0; */
/* } */

/* int create_game_room(void) { */
/*     if (pthread_mutex_init(&mutex, NULL) != 0) { */
/*         perror("mutex init error"); */
/*         exit(1); */
/*     } */
/*     if (pthread_cond_init(&cond, NULL) != 0) { */
/*         perror("cond init error"); */
/*         exit(2); */
/*     } */
/*     int sockfd = init_server(); */
/*     int clientfd; */
/*     struct sockaddr_storage con_addr; */
/*     socklen_t sin_size; */
/*     pthread_t tid[4]; */
/*     int tid_num = 0; */
/*     struct game_room *room = malloc(sizeof(struct game_room)); */
/*     room->wait_for_opponent = 0; */

/*     listen(sockfd, 10); */
/*     while (tid_num < 5) { */
/*         sin_size = sizeof(con_addr); */
/*         clientfd = accept(sockfd, (struct sockaddr *)&con_addr, &sin_size);
 */
/*         if (room->wait_for_opponent == 0) { */
/*             room->chess = chess_init(); */
/*             room->main_player = clientfd; */
/*             pthread_create(&tid[tid_num], NULL, game_room, room); */
/*         } else { */
/*             room->rival = clientfd; */
/*             ++tid_num; */
/*             pthread_cond_signal(&cond); */
/*         } */

/*     } */

/*     return 0; */
/* } */
