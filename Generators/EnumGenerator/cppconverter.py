from parser import EnumDefinition
from pathlib import Path

def write_enum_file_cpp(definition: EnumDefinition, out_path: Path, og_file : str, namespace_removal: int):
    namespaces = og_file[:-2].split("/")

    for i in range(namespace_removal):
        namespaces[-2] = namespaces[-2] + namespaces[-1]
        namespaces = namespaces[:-1]

    enum_name = namespaces[-1]
    namespaces = namespaces[:-1]
    tabs = 0

    with open(out_path, "w") as f:
        # Header Guard
        f.write("#pragma once\n")
        f.write(f"#include \"{og_file}\"\n")

        def write_tabs():
            for i in range(tabs):
                f.write("\t")

        for name in namespaces:
            write_tabs()
            f.write(f"namespace {name} {{\n")
            tabs += 1

        write_tabs()
        f.write(f"enum class {enum_name} : {definition.base_type} {{\n")
        tabs += 1

        for name in definition.values.keys():
            write_tabs()
            f.write(f"{name} = {definition.name}_{name}")
            if name != list(definition.values.keys())[-1]:
                f.write(",")
            f.write("\n")

        tabs -= 1
        write_tabs()
        f.write("};\n")


        for _ in namespaces:
            tabs -= 1
            write_tabs()
            f.write("}\n")