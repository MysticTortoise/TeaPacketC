import os

os.chdir(os.path.dirname(os.getcwd()))
print(os.getcwd())

modules = list()

with open("generators/InitModuleList.txt", "r") as infile:
    for line in infile:
        modules.append(line.rstrip())

with open("include/TeaPacket/Bundled/Init.h", "w") as outfile:
    outfile.write("#include \"TeaPacket/Types/Numeric.h\"\n")

    for module in modules:
        outfile.write(f"#ifdef TeaPacket_{module}_Implemented\n")
        outfile.write(f"#include \"TeaPacket/{module}/{module}.h\"\n")
        outfile.write("#endif\n")

    outfile.write("\n\ntp_bool TP_Bundled_Init(void) {\n\n")

    for module in modules:
        outfile.write(f"\t#ifdef TeaPacket_{module}_Implemented\n")
        outfile.write(f"\tif(!TP_{module}_Init()) {{ return tp_false; }}\n")
        outfile.write(f"\t#endif\n\n")

    outfile.write("\treturn tp_true;\n")
    outfile.write("}\n")

with open("include/TeaPacket/Bundled/DeInit.h", "w") as outfile:
    for module in modules:
        outfile.write(f"#ifdef TeaPacket_{module}_Implemented\n")
        outfile.write(f"#include \"TeaPacket/{module}/{module}.h\"\n")
        outfile.write("#endif\n")

    outfile.write("\n\nvoid TP_Bundled_DeInit(void) {\n\n")

    for module in modules:
        outfile.write(f"\t#ifdef TeaPacket_{module}_Implemented\n")
        outfile.write(f"\tTP_{module}_DeInit();\n")
        outfile.write(f"\t#endif\n\n")

    outfile.write("}\n")


