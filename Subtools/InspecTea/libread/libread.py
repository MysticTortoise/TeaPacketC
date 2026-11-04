from pathlib import Path

from . import libfiletypes
from .symbol import Symbol

from .plugins import choose
from .plugins.base import LibReader


def read_symbols_from_file(file: Path) -> set[Symbol]:
    reader: LibReader | None = choose.choose_plugin()

    if reader is None:
        raise NotImplemented
    elif isinstance(reader, LibReader):
        return reader.read_symbols_from_file(file)
    else:
        raise Exception

def read_symbols_from_files(files: list[Path]) -> set[Symbol]:
    symbols = set()
    for file in files:
        symbols.update(read_symbols_from_file(file))
    return symbols

def search_for_symbol_files(dir: Path) -> list[Path]:
    return list(Path(f) for f in dir.rglob("*") if len(f.suffix) > 1 and f.suffix.lower()[1:] in libfiletypes.file_types)

