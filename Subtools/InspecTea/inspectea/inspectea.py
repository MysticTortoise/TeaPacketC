from pathlib import Path

import clang

from . import cfuncdef
from .header_info import HeaderReflectInfo


def reflect_header(code) -> HeaderReflectInfo:
    info = HeaderReflectInfo()
    reflect_header_chained(code, info)

    return info

def reflect_header_file(path: Path) -> HeaderReflectInfo:
    with open(path, "r") as infile:
        code = infile.read()
    return reflect_header(code)

def reflect_header_file_chained(path: Path, info: HeaderReflectInfo):
    with open(path, "r") as infile:
        code = infile.read()
    reflect_header_chained(code, info)

def reflect_header_files(paths: list[Path]) -> HeaderReflectInfo:
    info = HeaderReflectInfo()
    for path in paths:
        reflect_header_chained(path, info)

    return info


def reflect_header_chained(code: str, info: HeaderReflectInfo):
    index = clang.cindex.Index.create()

    translate_unit = index.parse(
        path="dummy.h",
        unsaved_files=[("dummy.h", code)],
    )

    for node in translate_unit.cursor.walk_preorder():
        info.add_token(node)

