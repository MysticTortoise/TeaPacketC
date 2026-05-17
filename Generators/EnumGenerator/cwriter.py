from parser import EnumDefinition
from pathlib import Path

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

        f.write("#else\n")  # end of enum underlying
        # Fallback to C89

        f.write(f"typedef {definition.base_type} {definition.name};\n")

        for name in definition.values.keys():
            f.write(f"#define {definition.name}_{name} {definition.values[name]}\n")

        f.write("#endif\n")  # end of fallback

        # End header guard
        f.write("#endif")