import os
import shutil

# Copyright (C) 2026 Kevin "MysticTortoise" Tessier

# Python script to generate the Doxyfile used by TeaPacket.

def generate_doxyfile():
    # CHANGE  CWD
    old_cwd = os.getcwd()
    os.chdir(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

    # GET LIST OF MODULES
    modules:list[str] = list()
    modules_folder:str = os.path.dirname(os.getcwd()) + "/Modules"

    for folder in os.listdir(modules_folder):
        if not os.path.isdir(modules_folder + "/" + folder):
            continue
        modules.append(folder)

    to_add:str = ""

    # ADD INPUTS
    to_add += "INPUT = "
    for module in modules:
        to_add += f"../Modules/{module}/Interface/include "
    to_add += "\n"

    # ADD STRIP
    to_add += "STRIP_FROM_PATH = "
    for module in modules:
        to_add += f"../Modules/{module}/Interface/include/TeaPacket "
    to_add += "\n"


    # GENERATE OUT FILE
    shutil.copy("Template.doxyfile", "Doxyfile")
    with open("Doxyfile", "a") as doxyfile:
        doxyfile.write("\n")
        doxyfile.write(to_add)

    # RETUrn TO OLD CWD
    os.chdir(old_cwd)


if __name__ == "__main__":
    generate_doxyfile()