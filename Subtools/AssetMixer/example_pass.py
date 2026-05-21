from pathlib import Path
import sys, os

types = ("*.txt", "*.text")

def asset_pass(asset_dir):
    sys.path.append(os.path.dirname(__file__))

    files_to_convert = []
    path_to_search = Path(asset_dir)
    for filetype in types:
        files_to_convert.extend(path_to_search.rglob(filetype))

    for file_path in files_to_convert:
        if not file_path.is_file():
            continue

        with open(file_path, "a") as file:
            file.write("Hello, World!")

    sys.path.pop()