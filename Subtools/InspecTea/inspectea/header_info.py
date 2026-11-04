from clang.cindex import Cursor, CursorKind

from .cfuncdef import CFunc

class HeaderReflectInfo:
    functions: list[CFunc]

    def __init__(self):
        self.functions = list()

    def add_token(self, cursor: Cursor):
        if cursor.kind == CursorKind.FUNCTION_DECL:
            self.functions.append(CFunc(cursor))
            return

        if cursor.kind == CursorKind.TYPEDEF_DECL:
            #print(cursor.spelling)
            return

        #print(cursor.kind)



    def print_all(self):
        print("Functions ==========")
        for func in self.functions:
            print(f"\t{func}")