from pathlib import Path
from constants import ASM, SRC

def normalize_object_path(path: Path, prefix_path: Path):
    '''
    Standardize an object file path. For example, if
    `path/to/src/folder/file.c.o` is passed, return
    `{prefix_path}/src/folder/file.c.o`.
    '''
    path_str = path.as_posix()
    path_str = relative_to_name(path_str, SRC)
    path_str = relative_to_name(path_str, ASM)
    return (prefix_path / path_str).as_posix()

def relative_to_name(path_str: str, folder: str):
    '''
    Get path after and including a certain folder name. Similar to
    `Path.relative_to`, but works with a string instead of a known path.
    '''
    folder = f"{folder}/"
    if folder in path_str:
        path_str = folder + path_str.split(folder)[1]
    return path_str

def to_expected_path(base_path: str):
    '''
    Convert a compiled source file's object path to a corresponding expected
    path, assembled from an `.s` file of the same name.
    '''
    base_path = base_path.replace(".c.o", ".s.o")
    base_path = base_path.replace(f"{SRC}/", f"{ASM}/")
    return Path(base_path)

def ensure_path_and_write(output_path: Path, contents: str):
    output_path.parent.mkdir(exist_ok=True, parents=True)
    with open(output_path, "w") as f:
        f.write(contents)
