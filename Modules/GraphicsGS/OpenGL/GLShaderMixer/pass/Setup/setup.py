import os.path
import subprocess
from pathlib import Path

from .paths import c_build_dir, c_build_dir_name, c_proj_dir, app_dir_path

def setup():
    if not os.path.exists(c_build_dir):
        print("Configuring CMAKE for GLShaderMixer")
        subprocess.run(f"cmake -B {c_build_dir_name} -DCMAKE_BUILD_TYPE=Release", cwd=c_proj_dir, shell=True)

    print("Building GLShaderMixer")
    subprocess.run(f"cmake --build . --config Release", cwd=c_build_dir, shell=True)