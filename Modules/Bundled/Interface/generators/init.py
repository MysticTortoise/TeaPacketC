import os

# Copyright (C) 2026 Kevin "MysticTortoise" Tessier

# Python script to generate the headers included in the "Bundled" Module Interface

os.chdir(os.path.dirname(os.getcwd()))
print(os.getcwd())

class TPModule:
    name: str
    include: str

modules = list()

with open("generators/InitModuleList.txt", "r") as infile:
    for line in infile:
        list_arg = line.rstrip().split(" ")

        module = TPModule()
        module.name = list_arg[0]
        if len(list_arg) > 1:
            module.include = list_arg[1]
        else:
            module.include = f"TeaPacket/{module.name}/{module.name}.h"

        modules.append(module)

with open("include/TeaPacket/Bundled/Init.h", "w") as outfile:
    outfile.write("#include \"TeaPacket/Types/Numeric.h\"\n")
    outfile.write("#include \"TeaPacket/MacroUtils/Features.h\"\n")

    for module in modules:
        outfile.write(f"#ifdef TeaPacket_{module.name}_Implemented\n")
        outfile.write(f"#include \"{module.include}\"\n")
        outfile.write("#endif\n")

    outfile.write("#ifdef __cplusplus\nextern \"C\" {\n#endif")

    outfile.write("\n\nTP_INLINE_FUNC tp_bool TP_Bundled_Init(void) {\n\n")

    for module in modules:
        outfile.write(f"\t#ifdef TeaPacket_{module.name}_Implemented\n")
        outfile.write(f"\tif(!TP_{module.name}_Init()) {{ return tp_false; }}\n")
        outfile.write(f"\t#endif\n\n")

    outfile.write("\treturn tp_true;\n")
    outfile.write("}\n")

    outfile.write("#ifdef __cplusplus\n}\n#endif")

with open("include/TeaPacket/Bundled/DeInit.h", "w") as outfile:
    for module in modules:
        outfile.write(f"#ifdef TeaPacket_{module.name}_Implemented\n")
        outfile.write(f"#include \"{module.include}\"\n")
        outfile.write("#endif\n")

    outfile.write("#ifdef __cplusplus\nextern \"C\" {\n#endif")

    outfile.write("\n\nstatic void TP_Bundled_DeInit(void) {\n\n")

    for module in modules:
        outfile.write(f"\t#ifdef TeaPacket_{module.name}_Implemented\n")
        outfile.write(f"\tTP_{module.name}_DeInit();\n")
        outfile.write(f"\t#endif\n\n")

    outfile.write("}\n")

    outfile.write("#ifdef __cplusplus\n}\n#endif")


