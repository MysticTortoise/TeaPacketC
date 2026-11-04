from clang import cindex


class CFuncType:
    name: str

    def __init__(self, cursor: cindex.Cursor):
        self.name = cursor.spelling

    def __str__(self) -> str:
        return f"{self.name}"

class CFuncArg:
    name: str
    type: CFuncType

    def __init__(self, cursor: cindex.Cursor):
        self.name = cursor.spelling
        self.type = CFuncType(cursor.type)


    def __str__(self) -> str:
        return f"{self.type} {self.name}"

class CFunc:
    name: str
    args: list[CFuncArg]


    def __init__(self, cursor: cindex.Cursor):
        self.name = cursor.spelling
        self.args = list()

        for arg in cursor.get_arguments():
            self.args.append(CFuncArg(arg))


    def __str__(self) -> str:
        argstring = ",".join(str(x) for x in self.args)

        return f"{self.name}({argstring});"