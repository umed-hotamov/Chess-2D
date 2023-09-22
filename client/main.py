import pygame
from game_states import *
from screen import Screen

def run():
    pygame.init()
    screen = Screen()
    controller = Controller()
    controller.set_state(MainMenuState(controller, screen))
    controller.run()

if __name__ == '__main__':
    run()
