class Game():
    def __init__(self, screen):
        self.screen = screen
        self.DIMENSION = 8
        self.SQ_SIZE = self.screen.HEIGHT // self.DIMENSION 
        self.white_won = False
        self.black_won = False
        self.valid_moves = None
        self.board = [
            'bR', 'bN', 'bB', 'bQ', 'bK', 'bB', 'bN', 'bR',
            'bP', 'bP', 'bP', 'bP', 'bP', 'bP', 'bP', 'bP',
            '-', '-', '-', '-', '-', '-', '-', '-',
            '-', '-', '-', '-', '-', '-', '-', '-',
            '-', '-', '-', '-', '-', '-', '-', '-',
            '-', '-', '-', '-', '-', '-', '-', '-',
            'wp', 'wp', 'wp', 'wp', 'wp', 'wp', 'wp', 'wp',
            'wr', 'wn', 'wb', 'wq', 'wk', 'wb', 'wn', 'wr',
        ]
    
    def convert_to_board(self, response):
        rank = file = 0
        response = list(response)
        rc = response.pop()
        print(rc)
        for i in response:
            if i == '/':
                rank += 1
                file = 0
                continue
            elif i.isupper() and i != '-':
                i = 'b' + i
            elif i != '-':
                i = 'w' + i
            self.board[rank * self.DIMENSION + file] = i
            file += 1
