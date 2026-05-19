import os
import shutil


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
    for module in modules:
        to_add += f"INPUT += ../Modules/{module}/Interface/include\n"


    # GENERATE OUT FILE
    shutil.copy("Template.doxyfile", "Doxyfile")
    with open("Doxyfile", "a") as doxyfile:
        doxyfile.write("\n")
        doxyfile.write(to_add)

    # RETUrn TO OLD CWD
    os.chdir(old_cwd)


if __name__ == "__main__":
    generate_doxyfile()