from abc import ABC, abstractmethod
from pathlib import Path

from ..symbol import Symbol

class LibReader(ABC):
    @abstractmethod
    def read_symbols_from_file(self, file:Path) -> set[Symbol]:
        pass