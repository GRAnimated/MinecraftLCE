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
TARGET_UNCOMPRESSED_NSO_PATH = setup.config.get_versioned_data_path(setup.config.get_default_version()) / 'main.uncompressed.nso'

def prepare_executable(original_nso: Optional[Path]):
    COMPRESSED_HASH = "63b7d29503400853c2cdb87a65d963cb9b5b934aea9d3d88b55764d33b13a722"
    UNCOMPRESSED_HASH = "f408dbfb901ab191fbcb7b5994580ed91812bafa90ae164796ae8a254e4dcef8"

    target_hash = hashlib.sha256(TARGET_PATH.read_bytes()).hexdigest()

    if TARGET_PATH.is_file() and target_hash == COMPRESSED_HASH or target_hash == UNCOMPRESSED_HASH and TARGET_ELF_PATH.is_file():
        print(">>> NSO is already set up")
        return

    if original_nso is None:
        setup.fail("please pass a path to the NSO (refer to the readme for more details)")

    if not original_nso.is_file():
        setup.fail(f"{original_nso} is not a file")

    nso_hash = hashlib.sha256(original_nso.read_bytes()).hexdigest()

    if nso_hash == UNCOMPRESSED_HASH:
        print(">>> found uncompressed NSO")

    elif nso_hash == COMPRESSED_HASH:
        print(">>> found compressed NSO")

    else:
        setup.fail(f"unknown executable: {nso_hash}")

    setup._convert_nso_to_elf(original_nso)

    converted_elf_path = original_nso.with_suffix(".elf")

    if not converted_elf_path.is_file():
        setup.fail("internal error while preparing executable (missing ELF); please report")

    shutil.move(converted_elf_path, TARGET_ELF_PATH)

    uncompressed_nso_path = original_nso.with_suffix(".uncompressed.nso")
    shutil.move(uncompressed_nso_path, TARGET_UNCOMPRESSED_NSO_PATH)

    if not TARGET_UNCOMPRESSED_NSO_PATH.is_file() or hashlib.sha256(TARGET_UNCOMPRESSED_NSO_PATH.read_bytes()).hexdigest() != UNCOMPRESSED_HASH:
        setup.fail("Internal error while exporting uncompressed NSO (uncompressed NSO either doesn't exist or has an incorrect hash); please report")

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
    string_file = setup.ROOT / "toolchain/patches/string"
    string_target = setup.ROOT / "toolchain/clang-4.0.1/include/c++/v1/string"
    shutil.copyfile(string_file, string_target)
    
    locale_file = setup.ROOT / "toolchain/patches/locale"
    locale_target = setup.ROOT / "toolchain/clang-4.0.1/include/c++/v1/locale"
    shutil.copyfile(locale_file, locale_target)
    print(">>> Clang patched successfully")

def main():
    parser = argparse.ArgumentParser(
        "setup.py", description="Set up the decompilation project")
    parser.add_argument("original_nso", type=Path,
                        help="Path to the original NSO, compressed or not)", nargs="?")
    parser.add_argument("--project-only", action="store_true",
                    help="Disable original NSO setup")
    args = parser.parse_args()

    setup.install_viking()
    if not args.project_only:
        prepare_executable(args.original_nso)
    setup.set_up_compiler("4.0.1")
    create_build_dir()
    patch_clang()


if __name__ == "__main__":
    main()
