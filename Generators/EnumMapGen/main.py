import os, pathlib, sys

import itertools


class EnumDataList:
    typ : str = "data"

class EnumDef:
    is_class : bool = False
    name : str = ""
    alias : str = ""
    default : str = None

def generate(file, c_mode: Bool, up_to: int):
    dest_file = ""
    namespaces = set()
    headers = set()
    enums = list()
    error_message = "Invalid Enum"

    enum_map = list()

    submode_stack = list()

    with open(file, "r") as mapfile:
        for line in mapfile:
            words = line.strip().split(" ")
            command = words[0].lower()

            # END COMMAND
            if command == "end":
                
                submode_stack.pop()
                continue

            # PROCESS SUBMODES
            if len(submode_stack) > 0:
                if submode_stack[-1].typ == "data":
                    enum_map.append(words)
                continue
            
            # CHECK COMMANDS
            if command == "destination":
                dest_file = " ".join(words[1:])
            elif command == "namespaces":
                namespaces = set(words[1:])
            elif command == "headers":
                headers = set(words[1:])
            elif command == "enum":
                enumclass = EnumDef()
                ptr = 1
                if words[1].lower() == "class":
                    ptr = 2
                    enumclass.is_class = True
                
                enumclass.name = words[ptr]
                enumclass.alias = enumclass.name
                
                if len(words) > ptr+1:
                    if words[ptr+1].lower() == "alias":
                        enumclass.alias = words[ptr+2]
                enums.append(enumclass)
            elif command == "data":
                submode_stack.append(EnumDataList())
            elif command == "error":
                error_message = " ".join(words[1:])
            elif command == "default":
                for i in range(len(words)-1):
                    enums[i].default = words[i+1]
            
    if dest_file == "":
        print("NO DESTINATION FILE SET FOR " + file + " MAPGEN")
        return


    dest_file_path = os.getcwd() + "/include/" + dest_file
    pathlib.Path(os.path.dirname(dest_file_path)).mkdir(parents=True, exist_ok=True)
    with open(dest_file_path, "w+") as genfile:
        mypath = pathlib.Path(__file__).resolve().parent
        with open(f"{mypath}/header.hpp", "r") as headerFile:
            genfile.write(headerFile.read())

        for header in headers:
            genfile.write("#include " + header + "\n")
        for namespace in namespaces:
            genfile.write("using namespace " + namespace + ";\n")

        for enum in itertools.islice(enums,up_to):
            for other_enum in enums:
                if other_enum == enum:
                    continue

                # Generate Conversion
                if c_mode:
                    func_preline = "TP_INLINE_FUNC "
                else:
                    func_preline = "constexpr inline "

                genfile.write(func_preline + other_enum.name + " " + enum.alias + "To" + other_enum.alias + "(const " + enum.name + " val)\n")
                genfile.write("{\n")
                genfile.write(" switch(val)\n")
                genfile.write(" {\n")

                if enum.is_class:
                    genfile.write(" using enum " + enum.name + ";\n")
                if other_enum.is_class:
                    genfile.write(" using enum " + other_enum.name + ";\n")

                this_index = enums.index(enum)
                other_index = enums.index(other_enum)

                in_values:set = set()

                for i in range(len(enum_map)):
                    enum_in_val = enum_map[i][this_index]
                    if enum_in_val in in_values:
                        continue
                    in_values.add(enum_in_val)
                    genfile.write("case " + enum_in_val + ": return " + enum_map[i][other_index] + ";\n")
                if other_enum.default is None:
                    genfile.write("default: throw std::runtime_error(\"" + error_message + "\");\n")
                else:
                    genfile.write(f"default: return {other_enum.default};\n")

                genfile.write(" }\n")
                genfile.write("}\n")

                # Generate "Is Possible?" function
                genfile.write(func_preline + "tp_bool " + enum.alias + "ConvertableTo" + other_enum.alias + "(const " + enum.name + " val)\n")
                genfile.write("{\n")
                genfile.write(" switch(val)\n")
                genfile.write(" {\n")

                if enum.is_class:
                    genfile.write(" using enum " + enum.name + ";\n")
                if other_enum.is_class:
                    genfile.write(" using enum " + other_enum.name + ";\n")

                this_index = enums.index(enum)
                other_index = enums.index(other_enum)

                used_enums = set()

                for i in range(len(enum_map)):
                    i_enum = enum_map[i][this_index]
                    if i_enum in used_enums:
                        continue
                    used_enums.add(i_enum)
                    genfile.write("case " + i_enum + ":\n")

                genfile.write("return tp_true;\n")
                genfile.write("default: return tp_false;\n")

                genfile.write(" }\n")
                genfile.write("}\n")

        with open(f"{mypath}/footer.hpp", "r") as footerFile:
            genfile.write(footerFile.read())

if __name__ == "__main__":
    import argparse

    parser = argparse.ArgumentParser()

    parser.add_argument("gmap_file", help="gmap file to generate")
    parser.add_argument("--c_mode", "-c", help="Generates in c mode instead of c++", action="store_true")
    parser.add_argument("--max_from", help="Only generates From A to B for the first N enums.", type=int, default=9999)

    args = parser.parse_args()

    generate(args.gmap_file, args.c_mode, args.max_from)