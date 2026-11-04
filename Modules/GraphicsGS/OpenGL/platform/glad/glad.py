import os, subprocess, shutil, sys

dir = os.path.dirname(__file__)
python_name = sys.executable

def check():
    return os.path.isdir(os.path.join(dir, "glad"))

def grab():
    if not os.path.isdir(dir):
        os.makedirs(dir, exist_ok=True)

    print("Grabbing glad", flush=True)
    subprocess.run("git clone https://github.com/Dav1dde/glad.git", shell=True, cwd=dir)
    glad_dir = os.path.join(os.getcwd(), "glad")

    os.chdir(glad_dir)

    subprocess.run([sys.executable, "-m", "pip", "install", "-r", "requirements.txt"])



def setup():
    if not check():
        grab()

if __name__ == "__main__":
    setup()