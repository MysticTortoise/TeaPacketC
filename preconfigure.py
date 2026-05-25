import os, glob
import subprocess

abspath:str = os.path.abspath(__file__)
dname = os.path.dirname(abspath)
os.chdir(dname)

for file in glob.glob("./**/preconfigure.py", recursive=True):
    abs_file_path = os.path.abspath(file)
    if abs_file_path == abspath:
        continue
    subprocess.call(f'python "{abs_file_path}"')