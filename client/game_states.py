import pygame
from network import Network
from state import State
from button import Button
from game import Game
from controller import Controller

class MainMenuState(State):
    def __init__(self, controller, screen):
        self.controller = controller
        self.screen = screen
        self.GameModeState = False
        self.start_button = None

    def update(self):
        if self.GameModeState:
            self.controller.set_state(GameModeState(self.controller, self.screen))

    def render(self):
        self.screen.sc.blit(self.screen.BACKGROUND, (0, 0))
        mouse_pos = pygame.mouse.get_pos()

        menu_text = self.get_font(70).render('MAIN MENU', True, self.screen.WHITE)
        menu_rect = menu_text.get_rect(center=(self.screen.MID_WIDTH, self.screen.MID_HEIGHT - 200))
        self.screen.sc.blit(menu_text, menu_rect)

        self.start_button = Button(pos=(self.screen.MID_WIDTH, self.screen.MID_HEIGHT- 40),
                    text_input='Play', font=self.get_font(50),
                    base_color=self.screen.WHITE, hovering_color=self.screen.YELLOW)

        self.screen.sc.blit(menu_text, menu_rect)

        self.start_button.change_color(mouse_pos)
        self.start_button.update(self.screen.sc)

        pygame.display.update()

    def handle_input(self):
        mouse_pos = pygame.mouse.get_pos()
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                self.controller.quit()
            if event.type == pygame.MOUSEBUTTONDOWN:
                if self.start_button.mouse_clicked(mouse_pos):
                    self.GameModeState = True

    def get_font(self, size):
        return pygame.font.SysFont('freemonot.ttf', size)

class GameModeState(State):
    def __init__(self, controller, screen):
        self.controller = controller
        self.screen = screen
        self.mode_1 = None
        self.mode_2 = None
        self.game_state = False

    def update(self):
        if self.game_state:
            self.controller.set_state(GameState(self.controller, self.screen))

    def render(self):
        self.screen.sc.blit(self.screen.BACKGROUND, (0, 0))
        mouse_pos = pygame.mouse.get_pos()

        self.mode_1 = Button(pos=(self.screen.MID_WIDTH, self.screen.MID_HEIGHT - 90),
                    text_input='Play online', font=self.get_font(50),
                    base_color=self.screen.WHITE, hovering_color=self.screen.YELLOW)
        self.mode_2 = Button(pos=(self.screen.MID_WIDTH, self.screen.MID_HEIGHT - 50),
                    text_input='Play against computer', font=self.get_font(50),
                     base_color=self.screen.WHITE, hovering_color=self.screen.YELLOW)

        for button in [self.mode_1, self.mode_2]:
            button.change_color(mouse_pos)
            button.update(self.screen.sc)

        pygame.display.update()

    def handle_input(self):
        mouse_pos = pygame.mouse.get_pos()
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                self.controller.quit()
            if event.type == pygame.MOUSEBUTTONDOWN:
                if self.mode_1.mouse_clicked(mouse_pos):
                    self.game_state = True

    def get_font(self, size):
        return pygame.font.SysFont('freemonot.ttf', size)


class GameState(State):
    def __init__(self, controller, screen):
        self.network = Network()
        self.network.connect_to_server()
        self.game = Game(screen)
        self.controller = controller
        self.screen = screen
        self.main_menu_state = False
        self.mouse_clicked = False
        self.IMAGES = self.load_images()
        self.player_clicks = []
        self.selected_square = ()

    def update(self):
        if self.mouse_clicked:
            mouse_pos = pygame.mouse.get_pos()
            col = mouse_pos[0] // self.game.SQ_SIZE
            row = mouse_pos[1] // self.game.SQ_SIZE

            move_from = None
            move_to = None

            self.selected_square = (row, col)
            self.player_clicks.append(self.selected_square)

            if len(self.player_clicks) == 1:
                move_from = ''.join([str(i) for i in self.player_clicks[0]])
                self.network.send_request(move_from)
                self.game.valid_moves = list(map(int, list(self.network.get_response())))

            if len(self.player_clicks) == 2:
                move_to = ''.join([str(i) for i in self.player_clicks[1]])
                self.network.send_request(move_to)
                row = int(move_to[0])
                col = int(move_to[1])
                response = self.network.get_response()
                if self.game.valid_moves[row * self.game.DIMENSION + col]:
                    self.game.convert_to_board(response)
                    self.player_clicks = []
                    self.selected_square = ()
                else:
                    self.player_clicks = [self.selected_square]
                    move_from = ''.join([str(i) for i in self.player_clicks[0]])
                    self.network.send_request(move_from)
                    self.game.valid_moves = list(map(int, list(self.network.get_response())))

            self.mouse_clicked = False

    def render(self):
        self.draw_board()
        self.draw_hints()
        self.draw_pieces()
        pygame.display.update()

    def handle_input(self):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                self.controller.quit()
                self.network.close_connection()
            if event.type == pygame.MOUSEBUTTONDOWN:
                self.mouse_clicked = True

    def load_images(self):
        IMAGES = {}
        pieces = ['wp', 'wr', 'wn', 'wb', 'wk', 'wq',
                  'bP', 'bR', 'bN', 'bB', 'bK', 'bQ']

        for piece in pieces:
            IMAGES[piece] = pygame.transform.scale(
                pygame.image.load('images/chess_pieces/' + piece + '.png'), (self.game.SQ_SIZE, self.game.SQ_SIZE))

        return IMAGES

    def draw_board(self):
        colors = [pygame.Color('white'), pygame.Color('grey')]
        for row in range(self.game.DIMENSION):
            for col in range(self.game.DIMENSION):
                color = colors[((row + col) % 2)]
                pygame.draw.rect(self.screen.sc, color,
                                 pygame.Rect(col*self.game.SQ_SIZE, row*self.game.SQ_SIZE, self.game.SQ_SIZE, self.game.SQ_SIZE))

    def draw_pieces(self):
        for row in range(self.game.DIMENSION):
            for col in range(self.game.DIMENSION):
                piece = self.game.board[row * self.game.DIMENSION + col]
                if piece != '-':
                    self.screen.sc.blit(self.IMAGES[piece],
                                        pygame.Rect(col*self.game.SQ_SIZE, row*self.game.SQ_SIZE, self.game.SQ_SIZE, self.game.SQ_SIZE))


    def draw_hints(self):
        if self.selected_square != ():
            row, col = self.selected_square
            if self.game.board[row * self.game.DIMENSION + col] != '-':
                sq = pygame.Surface((self.game.SQ_SIZE, self.game.SQ_SIZE))
                sq.set_alpha(100)
                sq.fill(pygame.Color('blue'))
                self.screen.sc.blit(sq, (col * self.game.SQ_SIZE, row * self.game.SQ_SIZE))

                sq.fill(pygame.Color('green'))
                for row in range(self.game.DIMENSION):
                    for col in range(self.game.DIMENSION):
                        if self.game.valid_moves[row * self.game.DIMENSION + col]:
                            self.screen.sc.blit(sq, (col * self.game.SQ_SIZE, row * self.game.SQ_SIZE))
