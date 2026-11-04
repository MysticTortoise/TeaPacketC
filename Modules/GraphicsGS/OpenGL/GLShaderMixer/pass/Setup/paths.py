from pathlib import Path

c_proj_dir = Path(__file__).parent.parent.parent / "c"
c_build_dir_name = "build"
c_build_dir = c_proj_dir / c_build_dir_name
app_dir_path = c_build_dir / "cli"