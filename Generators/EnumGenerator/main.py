import sys
from pathlib import Path


class EnumDefinition:
    name: str
    base_type: str
    values: dict[str, int]

def parse_enum_file(input_file: Path):
    with open(input_file, 'r') as f:
        enum_def = EnumDefinition()

        # Parse Header
        line = f.readline()
        broken = line.split()

        enum_def.name = broken[0]
        if len(broken) == 1:
            enum_def.base_type = "int"
        if len(broken) == 2:
            enum_def.base_type = broken[1]
        else:
            raise Exception("Too many parameters in header!!")

        enum_def.values = dict()

        # Parse lines
        for line in f:
            broken = line.split()

            name = broken[0]
            if len(broken) == 1:
                if len(enum_def.values) <= 0:
                    val = 0
                else:
                    val = list(enum_def.values.values())[-1] + 1
            elif len(broken) == 3:
                if broken[1] != "=":
                    raise Exception(f"Invalid character at line: {line}")
                val = int(broken[2], 0)
            else:
                raise Exception(f"Too many parameters in line: {line}")

            if name in enum_def.values:
                raise Exception(f"Duplicate listing of: {name}")

            enum_def.values[name] = val
    return enum_def

def write_enum_file_interface(definition: EnumDefinition, out_path: Path):
    with open(out_path, "w") as f:
        # Header Guard
        f.write(f"#ifndef TEAPACKET_ENUM_{definition.name}\n")
        f.write(f"#define TEAPACKET_ENUM_{definition.name}\n")

        # Includes
        f.write("#include \"TeaPacket/Types/Numeric.h\" \n")
        f.write("#include \"TeaPacket/MacroUtils/Features.h\" \n")


        # Enum underlying type (C23 and C++ 11)
        f.write("#if TP_C_VER >= TP_C_VER23 || (defined(__cplusplus) && __cplusplus >= 201103L)\n")

        f.write(f"typedef enum : {definition.base_type} {{ \n")

        for name in definition.values.keys():
            f.write(f"\t{definition.name}_{name} = {definition.values[name]}")
            if name != list(definition.values.keys())[-1]:
                f.write(",")
            f.write("\n")

        f.write(f"}} {definition.name};\n")

        f.write("#else\n") # end of enum underlying
        # Fallback to C89

        f.write(f"typedef {definition.base_type} {definition.name};\n")

        for name in definition.values.keys():
            f.write(f"#define {definition.name}_{name} {definition.values[name]}\n")

        f.write("#endif\n") # end of fallback

        # End header guard
        f.write("#endif")

def generate(input_file, output_file):
    write_enum_file_interface(parse_enum_file(input_file), output_file)


if __name__ == "__main__":
    generate(sys.argv[1], sys.argv[2])