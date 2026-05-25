import os

def generate_common_vars():
    # CHANGE  CWD
    old_cwd = os.getcwd()
    os.chdir(os.path.dirname(os.path.abspath(__file__)))

    # GET LIST OF MODULES
    modules:list[str] = list()
    modules_folder:str = os.path.dirname(os.getcwd()) + "/Modules"

    for folder in os.listdir(modules_folder):
        if not os.path.isdir(modules_folder + "/" + folder):
            continue
        modules.append(folder)

    # Sort module list
    interface_only_modules:list[str] = list()
    has_impl_modules: list[str] = list()
    for module in modules:
        module_path = modules_folder + "/" + module
        folder_count = 0

        for folder in os.listdir(module_path):
            if not os.path.isdir(module_path + "/" + folder):
                continue
            folder_count = folder_count + 1

        if folder_count > 1:
            has_impl_modules.append(module)
        else:
            interface_only_modules.append(module)


    with open("CommonConsts.CMake", "w") as consts_file:
        consts_file.write("set(TP_MODULE_WITH_IMPL_LIST\n")
        for module in has_impl_modules:
            consts_file.write(f"\t\t{module}\n")
        consts_file.write(")\n")

        consts_file.write("set(TP_MODULE_NO_IMPL_LIST\n")
        for module in interface_only_modules:
            consts_file.write(f"\t\t{module}\n")
        consts_file.write(")\n")

        consts_file.write("set(TP_MODULE_LIST\n")
        for module in modules:
            consts_file.write(f"\t\t{module}\n")
        consts_file.write(")\n")



    # RETUrn TO OLD CWD
    os.chdir(old_cwd)


if __name__ == "__main__":
    generate_common_vars()