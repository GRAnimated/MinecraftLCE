#!/usr/bin/env python3

# Copied from https://github.com/MonsterDruide1/OdysseyDecomp/blob/master/tools/build.py

import argparse
from setup import get_build_dir
import subprocess
import os
import time
from common import setup_common as setup

project_root = setup.ROOT

def touch_cmake_lists():
    cmake_lists_path = project_root / 'CMakeLists.txt'
    os.utime(cmake_lists_path, times=None)

build_sources_path = get_build_dir() / '.build_sources'

def main():
    parser = argparse.ArgumentParser(
        'build.py', description="Build the decompilation project")
    parser.add_argument('--clean', action='store_true',
                        help="Clean before building")
    parser.add_argument('--verbose', action='store_true',
                        help="Give verbose output")
    args = parser.parse_args()

    if not get_build_dir().is_dir():
        print("Please run setup.py first.")
        exit(1)

    cmake_args = ['cmake', '--build', str(get_build_dir())]
    if args.clean:
        cmake_args.append('--clean-first')
    if args.verbose:
        os.environ['VERBOSE'] = '1'

    # Touch CMakeLists.txt if necessary, for reglobbing

    # Adding real source files
    real_source_paths = []
    for dir in [project_root/'src']:
        for root, _, files in os.walk(dir):
            for file in files:
                file_path = os.path.join(root, file)
                file_str = str(file_path)
                if file_str.endswith('.h') or file_str.endswith('.hpp') or file_str.endswith('.c') or file_str.endswith('.cpp'):
                    real_source_paths.append(str(file_path))

    # Checking if real files/files from build folder match
    with open(build_sources_path, 'r') as f:
        paths = f.read().splitlines()
        paths.sort()
        real_source_paths.sort()

        if paths != real_source_paths:
            touch_cmake_lists()

    subprocess.run(cmake_args)

if __name__ == "__main__":
    main()