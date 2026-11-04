import shutil

from .base import LibReader
from . import nm

def choose_plugin() -> LibReader | None:
    if shutil.which("nm") is not None:
        return nm.NMReader()

    return None