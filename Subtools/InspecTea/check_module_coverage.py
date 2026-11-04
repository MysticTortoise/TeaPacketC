from math import ceil, floor
from pathlib import Path

from inspectea import inspectea, HeaderReflectInfo
from libread import libread


def check_module_coverage(include_folder: Path, obj_folder: Path):
    header_files = include_folder.rglob("*.h")

    info = HeaderReflectInfo()
    for file in header_files:
        inspectea.reflect_header_file_chained(file, info)

    obj_files = libread.search_for_symbol_files(obj_folder)

    #print("Reading obj files:")
    #for file in obj_files:
    #    print(f"\t{file}")

    symbols = libread.read_symbols_from_files(obj_files)

    symbol_names = list((s.name for s in symbols))

    #for symbol in symbols:
        #print(f"Found symbol {symbol.name}")

    missing_symbols: set[str] = set()

    for func in info.functions:
        if func.name not in symbol_names:
            missing_symbols.add(func.name)

    for symbol in missing_symbols:
        print(f"Missing symbol {symbol}")

    want_symbol_count = len(info.functions)
    missing_symbol_count = len(missing_symbols)
    found_symbol_num = want_symbol_count - len(missing_symbols)

    percent_found = float(found_symbol_num) / want_symbol_count
    percent_missing = float(missing_symbol_count) / want_symbol_count

    bar_count = min(want_symbol_count, 50)

    print(f"Found {found_symbol_num}/{want_symbol_count} symbols | {missing_symbol_count} symbols missing.")

    true_blocks = floor(percent_found * bar_count)
    empty_blocks = ceil(percent_missing * bar_count)

    progbar = "["
    progbar += ('#' * true_blocks)
    progbar += (' ' * empty_blocks)
    progbar += "]"
    print(f"{progbar} | {round(percent_found * 100, 2)}% functions implemented")




if __name__ == "__main__":
    import argparse

    parser = argparse.ArgumentParser()

    parser.add_argument("include_folder", help="The include folder for the module.")
    parser.add_argument("lib_folder", help="The folder containing all the compiled static library files for the module.")

    args = parser.parse_args()

    print(args.include_folder)
    print(args.lib_folder)

    check_module_coverage(
        Path(args.include_folder),
        Path(args.lib_folder)
    )