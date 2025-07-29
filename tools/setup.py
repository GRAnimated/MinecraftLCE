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
import difflib

TARGET_PATH = setup.get_target_path()
TARGET_ELF_PATH = setup.get_target_elf_path()
TARGET_UNCOMPRESSED_NSO_PATH = setup.config.get_versioned_data_path(setup.config.get_default_version()) / 'main.uncompressed.nso'

PATCH_SOURCE_DIR = setup.ROOT / "toolchain/patches/generate"
PATCH_DEST_DIR = setup.ROOT / "toolchain/patches"
TOOLCHAIN_DIR = setup.ROOT / "toolchain/clang-4.0.1/include/c++/v1"


def file_sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def generate_diff(source: Path, target: Path, diff_path: Path, checksums_path: Path):
    original_lines = source.read_text().splitlines(keepends=True)
    modified_lines = target.read_text().splitlines(keepends=True)
    diff = list(difflib.unified_diff(original_lines, modified_lines, fromfile=source.name, tofile=target.name))

    diff_path.write_text("".join(diff))
    checksums_path.write_text(f"before: {file_sha256(source)}\nafter: {file_sha256(target)}\n")


def apply_diff(original: Path, diff_file: Path):
    result = subprocess.run(
        ["patch", "-N", str(original), str(diff_file)],
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True
    )

    if result.returncode == 0:
        return
    elif result.returncode == 1:
        combined_output = (result.stdout + result.stderr).lower()
        if ("reversed (or previously applied) patch detected" in combined_output or
            "skip" in combined_output or
            "ignoring" in combined_output):
            # its fine
            return
        else:
            raise RuntimeError(f"Patch failed with output:\n{result.stdout}\n{result.stderr}")
    else:
        raise RuntimeError(f"Patch command failed with code {result.returncode}:\n{result.stdout}\n{result.stderr}")



def is_diff_applied(original: Path, expected_hash: str) -> bool:
    return file_sha256(original) == expected_hash

def patch_clang(remake_diffs=False):
    redownloaded_clang = False
    for src in PATCH_SOURCE_DIR.iterdir():
        if not src.is_file():
            continue

        dst = TOOLCHAIN_DIR / src.name
        diff_file = PATCH_DEST_DIR / f"{src.name}.diff"
        checksum_file = PATCH_DEST_DIR / f"{src.name}.sha256"

        if remake_diffs and redownloaded_clang == False:
            clang_path = setup.ROOT / "toolchain/clang-4.0.1"
            if clang_path.exists():
                print(">>> Removing old clang toolchain")
                shutil.rmtree(clang_path)
            print(">>> Re-downloading clang toolchain")
            setup.set_up_compiler("4.0.1")
            redownloaded_clang = True
            
            generate_diff(dst, src, diff_file, checksum_file)

        print(f">>> Applying patch: {src.name}")
        apply_diff(dst, diff_file)

    print(">>> Clang patched successfully")


def check_diff_applied_status():
    status = {}
    for src in PATCH_SOURCE_DIR.iterdir():
        if not src.is_file():
            continue

        target_file = TOOLCHAIN_DIR / src.name
        checksum_file = PATCH_DEST_DIR / f"{src.name}.sha256"
        if not checksum_file.exists():
            status[src.name] = False
            continue
        expected_hash = checksum_file.read_text().splitlines()[-1].split("after: ")[-1]
        status[src.name] = is_diff_applied(target_file, expected_hash)
    return status


def prepare_executable(original_nso: Optional[Path]):
    COMPRESSED_HASH = "63b7d29503400853c2cdb87a65d963cb9b5b934aea9d3d88b55764d33b13a722"
    UNCOMPRESSED_HASH = "f408dbfb901ab191fbcb7b5994580ed91812bafa90ae164796ae8a254e4dcef8"

    target_hash = file_sha256(TARGET_PATH)

    if TARGET_PATH.is_file() and target_hash == COMPRESSED_HASH or target_hash == UNCOMPRESSED_HASH and TARGET_ELF_PATH.is_file():
        print(">>> NSO is already set up")
        return

    if original_nso is None:
        setup.fail("please pass a path to the NSO (refer to the readme for more details)")

    if not original_nso.is_file():
        setup.fail(f"{original_nso} is not a file")

    nso_hash = file_sha256(original_nso)

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

    if not TARGET_UNCOMPRESSED_NSO_PATH.is_file() or file_sha256(TARGET_UNCOMPRESSED_NSO_PATH) != UNCOMPRESSED_HASH:
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


def main():
    parser = argparse.ArgumentParser("setup.py", description="Set up the decompilation project")
    parser.add_argument("original_nso", type=Path, help="Path to the original NSO, compressed or not)", nargs="?")
    parser.add_argument("--project-only", action="store_true", help="Disable original NSO setup")
    parser.add_argument("--remake-diffs", action="store_true", help="Regenerate diff files for patched files stored in toolchain/patches/generate")
    args = parser.parse_args()

    setup.install_viking()
    if not args.project_only:
        prepare_executable(args.original_nso)
    setup.set_up_compiler("4.0.1")
    create_build_dir()
    patch_clang(remake_diffs=args.remake_diffs)


if __name__ == "__main__":
    main()
