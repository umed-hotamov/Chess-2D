import pygame

class Screen():
    def __init__(self):
        self.WIDTH = self.HEIGHT = 512
        self.MID_WIDTH = self.MID_HEIGHT = 512 // 2

        self.BLACK = (0, 0, 0)
        self.WHITE = (255, 255, 255)
        self.YELLOW = (255, 255, 0)
        self.BACKGROUND = pygame.image.load('images/bg/bg.jpg')
        self.BACKGROUND = pygame.transform.scale(self.BACKGROUND, (self.WIDTH, self.HEIGHT))

        self.sc = pygame.display.set_mode((self.WIDTH, self.HEIGHT))
