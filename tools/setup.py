#!/usr/bin/env python3

import argparse
import hashlib
from pathlib import Path
import subprocess
import tempfile
import urllib.request
from typing import Optional
from common import setup_common as setup
import shutil

TARGET_PATH = setup.get_target_path()
TARGET_ELF_PATH = setup.get_target_elf_path()

def prepare_executable(original_nso: Optional[Path]):
    COMPRESSED_HASH = "63b7d29503400853c2cdb87a65d963cb9b5b934aea9d3d88b55764d33b13a722"
    UNCOMPRESSED_HASH = "f408dbfb901ab191fbcb7b5994580ed91812bafa90ae164796ae8a254e4dcef8"

    TARGET_HASH = UNCOMPRESSED_HASH

    if TARGET_PATH.is_file() and hashlib.sha256(TARGET_PATH.read_bytes()).hexdigest() == TARGET_HASH and TARGET_ELF_PATH.is_file():
        print(">>> NSO is already set up")
        return

    if original_nso is None:
        setup.fail("please pass a path to the NSO (refer to the readme for more details)")

    if not original_nso.is_file():
        setup.fail(f"{original_nso} is not a file")

    nso_data = original_nso.read_bytes()
    nso_hash = hashlib.sha256(nso_data).hexdigest()

    if nso_hash == UNCOMPRESSED_HASH:
        print(">>> found uncompressed NSO")
        TARGET_PATH.write_bytes(nso_data)

    elif nso_hash == COMPRESSED_HASH:
        print(">>> found compressed NSO")
        setup._decompress_nso(original_nso, TARGET_PATH)

    else:
        setup.fail(f"unknown executable: {nso_hash}")

    if not TARGET_PATH.is_file():
        setup.fail("internal error while preparing executable (missing NSO); please report")
    if hashlib.sha256(TARGET_PATH.read_bytes()).hexdigest() != TARGET_HASH:
        setup.fail("internal error while preparing executable (wrong NSO hash); please report")

    setup._convert_nso_to_elf(TARGET_PATH)

    if not TARGET_ELF_PATH.is_file():
        setup.fail("internal error while preparing executable (missing ELF); please report")


def get_build_dir():
    return setup.ROOT / "build"

def create_build_dir():
    build_dir = setup.ROOT / "build"
    if build_dir.is_dir():
        print(">>> build directory already exists: nothing to do")
        return

    subprocess.check_call(
        "cmake -GNinja -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_TOOLCHAIN_FILE=toolchain/ToolchainNX64.cmake -DCMAKE_CXX_COMPILER_LAUNCHER=ccache -B build/".split(" "))
    print(">>> created build directory")

def patch_clang():
    patch_file = setup.ROOT / "toolchain/patches/string"
    target_file = setup.ROOT / "toolchain/clang-4.0.1/include/c++/v1/string"
    shutil.copyfile(patch_file, target_file)
    print(">>> Clang patched successfully")

def main():
    parser = argparse.ArgumentParser(
        "setup.py", description="Set up the decompilation project")
    parser.add_argument("original_nso", type=Path,
                        help="Path to the original NSO, compressed or not)", nargs="?")
    args = parser.parse_args()

    setup.install_viking()
    prepare_executable(args.original_nso)
    setup.set_up_compiler("4.0.1")
    create_build_dir()
    patch_clang()


if __name__ == "__main__":
    main()
