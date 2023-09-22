from abc import ABC, abstractmethod

class State(ABC):
    @abstractmethod
    def update():
        pass

    @abstractmethod
    def render():
        pass

    @abstractmethod
    def handle_input():
        pass
