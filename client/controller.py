class Controller():
    def __init__(self):
        self.__controller_state = None
        self.__running = False

    def run(self):
        self.__running = True
        while self.__running:
            self.__controller_state.handle_input()
            self.__controller_state.update()
            self.__controller_state.render()

    def set_state(self, state):
        self.__controller_state = state

    def quit(self):
        self.__running = False
