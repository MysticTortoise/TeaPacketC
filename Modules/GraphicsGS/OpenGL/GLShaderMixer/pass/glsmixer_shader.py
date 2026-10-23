from pathlib import Path
import sys, os, subprocess

vert_types = {"vert", "vs", "vsh"}
frag_types = {"frag", "fs", "fsh", "ps", "psh"}
types = vert_types | frag_types

#def get_updated_files(asset_source : str, asset_built : str):
#    pass

def asset_pass(asset_dir):
    sys.path.append(os.path.dirname(__file__))

    import Setup
    Setup.setup()

    files_to_convert = []
    path_to_search = Path(asset_dir)
    for filetype in types:
        files_to_convert.extend(path_to_search.rglob(f"*.{filetype}"))

    for file_path in files_to_convert:
        if not file_path.is_file():
            continue

        def run_command(command):
            try:
                subprocess.run(command, cwd=Setup.app_dir_path, shell=True,
                           check=True, capture_output=True, text=True, encoding='utf-8')
            except subprocess.CalledProcessError as e:
                print(f"SHADER COMPILATION FAILED! Error code: {e.returncode}", file=sys.stderr)
                print(f"STDOUT:{e.stdout}", file=sys.stderr)
                print(f"STDERR:{e.stderr}", file=sys.stderr)
                raise e

        shader_type = "NONE"
        if Path(file_path).suffix[1:] in vert_types:
            shader_type = "VERT"
        elif Path(file_path).suffix[1:] in frag_types:
            shader_type = "FRAG"


        #TODO: Platform settings
        run_command(f"./gl_shader_mixer_cli \"{file_path}\" \"{file_path}.conv\" --type {shader_type}"
                    f" --major 3 --minor 3 --platform GL")
        #run_command(f"glslangValidator.exe -H -V -o shader.spv {file_path}")
        #run_command(f"spirv-cross.exe --hlsl --shader-model 50 shader.spv --output {file_path}")
        os.replace(f"{file_path}.conv", file_path)

    sys.path.pop()