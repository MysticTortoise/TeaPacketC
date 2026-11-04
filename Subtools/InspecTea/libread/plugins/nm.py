from pathlib import Path
import subprocess
import re

from .base import LibReader, Symbol

regex_str = R"^((?:[A-Fa-f0-9]{8})+) ([ABbCDdGgiNpRrSsTtUuVvWw\-?]) (.*)$"

class NMReader(LibReader):
    def read_symbols_from_file(self, file:Path) -> set[Symbol]:
        symbols = set()

        command = f"nm -gUC \"{file.absolute()}\""
        result = subprocess.run(command, stdout=subprocess.PIPE, shell=True, text=True)

        output = result.stdout

        if False:
            print(command)
            print(output)

        matches = re.findall(regex_str, output, re.MULTILINE)

        for match in matches:
            #addr = match[0]
            #type = match[1]
            name = match[2]

            if name[0] == "_": # fix for MacOS mangling
                if name[1] == "_":
                    continue
                name = name[1:]

            symbol = Symbol(name)

            symbols.add(symbol)



        return symbols