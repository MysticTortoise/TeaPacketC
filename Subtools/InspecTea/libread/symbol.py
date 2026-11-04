

class Symbol:
    name: str

    def __init__(self, name:str):
        self.name = name


    def __str__(self) -> str:
        return f"{self.name}"