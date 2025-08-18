import os
import re
import json
import yaml
import argparse
import subprocess

# Some checks from https://github.com/MonsterDruide1/OdysseyDecomp/blob/master/tools/check-format.py

issueFound = False
runAllChecks = False

def FAIL(message, line, path):
    print("Offending file:", os.path.relpath(path, os.getcwd()))
    print("Line:", line)
    print(message)
    print()
    global issueFound
    issueFound = True

def CHECK(cond, line, message, path):
    if not cond(line):
        FAIL(message, line, path)
        return True
    return False

class CommonChecks:
    def __init__(self, c, path, cpp_class_map, fix=False, slow=False):
        self.c = c
        self.path = path
        self.fix = fix
        self.map = cpp_class_map

    def run(self):
        self.void_params()
        self.consistent_float_literals()
        self.absolute_include_paths()
        self.newline_after_last_include()
        self.newline_eof()
        return self.c

    def void_params(self):
        lines = self.c.splitlines()
        new_lines = []
        changed = False
        for line in lines:
            original_line = line
            if "(void);" in line or "(void) {" in line or "(void) const" in line:
                FAIL("Function parameters should be empty instead of \"(void)\"!", original_line, self.path)
                # FIX
                if self.fix:
                    line = line.replace("(void);", "();")
                    line = line.replace("(void) {", "() {")
                    line = line.replace("(void) const", "() const")
                    changed = True
            new_lines.append(line)

        if changed:
            self.c = "\n".join(new_lines)

    def consistent_float_literals(self):
        lines = self.c.splitlines()
        new_lines = []
        changed = False
        # float value = 1.f; becomes
        # float value = 1.0f;
        pattern = re.compile(r'\.f(?![a-zA-Z])')
        for line in lines:
            original_line = line
            if pattern.search(line):
                FAIL(" '.f' is not allowed, use '.0f' instead!", original_line, self.path)
                # FIX
                if self.fix:
                    line = pattern.sub('.0f', line)
                    changed = True
            new_lines.append(line)

        if changed:
            self.c = "\n".join(new_lines)

    def newline_eof(self):
        lines = self.c.splitlines()
        new_lines = lines[:]
        changed = False

        if not self.c.endswith("\n") or self.c.endswith("\n\n"):
            FAIL("Files should end with a single newline!", "", self.path)
            # FIX
            if self.fix:
                # remove extra newlines
                while new_lines and new_lines[-1] == "":
                    new_lines.pop()
                new_lines.append("")
                changed = True

        if changed:
            self.c = "\n".join(new_lines)

    def absolute_include_paths(self):
        lines = self.c.splitlines()
        new_lines = []
        changed = False

        for line in lines:
            original_line = line
            match = re.match(r'#include\s+"([^"]+)"', line)
            if match:
                include_path = match.group(1)
                absolute_path = next((path for path in self.map.values() if include_path in path), None)
                if absolute_path:
                    path = absolute_path.split('/', 1)
                    path = path[1] if len(path) > 1 else absolute_path
                    if not line.startswith(f'#include "{path}"'):
                        FAIL(f'Include path "{include_path}" should be absolute as "{path}"!', original_line, self.path)
                        # FIX
                        if self.fix:
                            line = f'#include "{path}"'
                            changed = True
            new_lines.append(line)

        if changed:
            self.c = "\n".join(new_lines)

    def newline_after_last_include(self):
        lines = self.c.splitlines()
        new_lines = []
        changed = False
        last_include_index = -1

        for i, line in enumerate(lines):
            original_line = line
            if line.strip().startswith("#include"):
                last_include_index = len(new_lines)
                new_lines.append(line)
            else:
                new_lines.append(line)

        if last_include_index != -1 and last_include_index + 1 < len(new_lines) and new_lines[last_include_index + 1].strip() != "":
            FAIL("There should be a newline after the last include!", new_lines[last_include_index], self.path)
            # FIX
            if self.fix:
                new_lines.insert(last_include_index + 1, "")
                changed = True

        if changed:
            self.c = "\n".join(new_lines)

class HeaderChecks:
    def __init__(self, c, path, cpp_class_map, fix=False, slow=False):
        self.c = c
        self.path = path
        self.fix = fix
        self.map = cpp_class_map

    def run(self):
        self.pragma_once()
        self.newline_after_pragma()
        self.virtual_override()
        return self.c

    def pragma_once(self):
        lines = self.c.splitlines()
        new_lines = []
        changed = False
        pragma_once_found = False

        for line in lines:
            original_line = line
            if "#pragma once" in line:
                pragma_once_found = True
                new_lines.append(line)
            elif line.strip().startswith("#include"):
                if not pragma_once_found:
                    FAIL("Header files should start with '#pragma once'!", original_line, self.path)
                    # FIX
                    if self.fix:
                        new_lines.insert(0, "#pragma once\n")
                        changed = True
                new_lines.append(line)
            else:
                new_lines.append(line)

        if not pragma_once_found and not changed:
            FAIL("Header files should start with '#pragma once'!", "", self.path)
            # FIX
            if self.fix:
                new_lines.insert(0, "#pragma once\n")
                changed = True

        if changed:
            self.c = "\n".join(new_lines)

    def newline_after_pragma(self):
        lines = self.c.splitlines()
        new_lines = []
        changed = False
        pragma_once_found = False

        for i, line in enumerate(lines):
            original_line = line
            if "#pragma once" in line:
                pragma_once_found = True
                new_lines.append(line)
                if i + 1 < len(lines) and lines[i + 1].strip() != "":
                    FAIL("There should be a newline after '#pragma once'!", original_line, self.path)
                    # FIX
                    if self.fix:
                        new_lines.append("")
                        changed = True
            else:
                new_lines.append(line)

        if changed:
            self.c = "\n".join(new_lines)

    def virtual_override(self):
        lines = self.c.splitlines()
        new_lines = []
        changed = False
        virtual_found = False

        for line in lines:
            original_line = line
            if "virtual " in line and "override" in line:
                virtual_found = True
                if line.strip().startswith("virtual "):
                    FAIL("Functions that are overridden should not have 'virtual'!", original_line, self.path)
                    # FIX
                    if self.fix:
                        line = line.replace("virtual ", "")
                        changed = True
            new_lines.append(line)

        if changed:
            self.c = "\n".join(new_lines)

class SourceChecks:
    def __init__(self, c, path, cpp_class_map, fix=False, slow=False):
        self.c = c
        self.path = path
        self.fix = fix
        self.map = cpp_class_map
        self.slow = slow

    def run(self):
        self.include_at_top()
        if self.slow:
            with open("src/Minecraft.Client/net/minecraft/client/ui/StringIDs.h", "r") as f:
                self.string_ids(f.read())
        return self.c

    # checks if the include for the current file is at the top of the file with a newline after
    def include_at_top(self):
        include_path = self.path.split('/', 2)
        include_path = include_path[2] if len(include_path) > 2 else self.path
        include_path = include_path.replace('.cpp', '.h')
        lines = self.c.splitlines()
        new_lines = []
        changed = False
        include_found = False

        for i, line in enumerate(lines):
            original_line = line
            if f'#include "{include_path}"' in line:
                include_found = True
                if i != 0:
                    FAIL(f'Include for "{include_path}" should be at the top of the file!', original_line, self.path)
                    # FIX
                    if self.fix:
                        new_lines.insert(0, f'#include "{include_path}"\n')
                        changed = True
                        continue # don't duplicate the line
                new_lines.append(line)
            else:
                new_lines.append(line)

        if changed:
            self.c = "\n".join(new_lines)

    def string_ids(self, id_file):
        lines = self.c.splitlines()
        new_lines = []
        changed = False

        for line in lines:
            original_line = line

            # 0xXXXXXXXX, signed, and unsigned ints
            pattern = r'(0x[0-9A-Fa-f]{8}|\b-?\d+\b)'
            matches = re.finditer(pattern, line)

            for match in matches:
                num_str = match.group(0)

                if num_str.startswith("0x") or num_str.startswith("0X"):
                    hex_id = num_str[2:].upper()
                else:
                    try:
                        num = int(num_str)
                        # handle signed wrapping if necessary
                        if num < 0:
                            num &= 0xFFFFFFFF
                        hex_id = f"{num:08X}"
                    except ValueError:
                        continue

                new_line, const_name, found = self.replace_id(id_file, line, hex_id, num_str)

                if found:
                    FAIL(f"{num_str} (0x{hex_id}) should be replaced with StringIDs::{const_name}!",
                        original_line, self.path)
                    if self.fix:
                        changed = True
                        line = new_line

            new_lines.append(line)

        if changed:
            self.c = "\n".join(new_lines)


    def replace_id(self, id_file, line, hex_id, num_str):
        pattern = r'constexpr u32 (\w+) = 0x' + hex_id
        match = re.search(pattern, id_file)
        if match:
            const_name = match.group(1)
            return line.replace(num_str, "StringIDs::" + const_name), const_name, True
        return line, "", False

def run_clang_format(file_path):
    try:
        print(f"Formatting {file_path}...")
        subprocess.run(['clang-format', '-i', file_path], check=True)
    except FileNotFoundError:
        print("Error: clang-format not found. Please install it or add it to your PATH.")
        exit(1)
    except subprocess.CalledProcessError:
        print(f"Error: clang-format failed on {file_path}")

SRC_DIR = "src"
CLASS_PATTERN = re.compile(r'^\s*(class|struct|enum)\s+(\w+) \{', re.MULTILINE)

def find_cpp_classes(src_dir):
    class_map = {}
    for root, _, files in os.walk(src_dir):
        for file in files:
            if file.endswith(('.h', '.hpp', '.cpp')):
                filepath = os.path.join(root, file)
                with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
                    content = f.read()
                    for match in CLASS_PATTERN.finditer(content):
                        kind, name = match.groups()
                        rel_path = os.path.relpath(filepath, src_dir).replace("\\", "/")

                        class_map[name] = rel_path
    return class_map

def flatten_nested_map(nested_map, prefix=""):
    flattened = []
    for key, value in nested_map.items():
        if key in ("_classes", "_enums"):
            for name in value:
                path = prefix.rstrip("/")
                flattened.append((name, path))
        elif isinstance(value, dict):
            new_prefix = f"{prefix}/{key}" if prefix else key
            flattened.extend(flatten_nested_map(value, new_prefix))
    return flattened

def load_class_map_yaml(filename):
    with open(filename, 'r', encoding='utf-8') as f:
        return yaml.safe_load(f)

def compare_class_locations(cpp_map, nested_class_map):
    mismatches = []
    expected_classes = flatten_nested_map(nested_class_map)
    expected_class_names = {name for name, _ in expected_classes}

    # check for mismatches where classes are in the wrong location
    for class_name, expected_path in expected_classes:
        cpp_location = cpp_map.get(class_name)
        if cpp_location:
            cpp_location_norm = cpp_location.replace("\\", "/")
            if expected_path not in cpp_location_norm:
                mismatches.append((class_name, f"Expected in '{expected_path}', found in '{cpp_location_norm}'"))

    # check for C++ classes that are not in the class map
    cpp_only = []
    for cpp_class in cpp_map:
        if cpp_class not in expected_class_names:
            cpp_only.append((cpp_class, cpp_map[cpp_class]))

    # check for unsorted classes in the YAML
    unsorted_classes = nested_class_map.get("unsorted", [])
    cpp_only_unsorted = []
    for unsorted_class in unsorted_classes:
        cpp_location = cpp_map.get(unsorted_class)
        if cpp_location:
            cpp_only_unsorted.append((unsorted_class, cpp_location))

    # check for classes that are in unsorted but exist within the nested class map
    for unsorted_class in unsorted_classes:
        if unsorted_class in expected_class_names:
            mismatches.append((unsorted_class, f"Class '{unsorted_class}' is marked as unsorted but exists in the nested class map."))

    return mismatches, cpp_only, cpp_only_unsorted

def write_fixes(file_path, modified_content):
    if modified_content:
        rel_path = os.path.relpath(file_path, os.getcwd())
        print(f"Fixing issues in {rel_path}")

        with open(file_path, 'w', encoding='utf-8', newline='') as f:
            f.write(modified_content)

def main():
    parser = argparse.ArgumentParser(description="Check and optionally fix decomp source file formatting.")
    parser.add_argument('--fix', action='store_true', help='Try to fix the formatting issues automatically.')
    parser.add_argument('--format', action='store_true', help='Run clang-format before checks.')
    parser.add_argument('--find-unsorted', action='store_true', help='Find unsorted classes/enums in the source files.')
    parser.add_argument('--slow', action='store_true', help='Run slow checks.')

    args = parser.parse_args()

    cpp_class_map = find_cpp_classes(SRC_DIR)
    nested_class_map = load_class_map_yaml("data/java_class_map.yaml")

    mismatches, cpp_only, cpp_only_unsorted = compare_class_locations(cpp_class_map, nested_class_map)
    
    if not mismatches:
        print("All classes/enums are in expected locations.")
    else:
        print("Mismatches found:")
        for name, issue in mismatches:
            print(f" - {name}: {issue}")

    # if cpp_only:
    #     print("\nClasses/enums only found in C++ but not in YAML:")
    #     for name, location in cpp_only:
    #         print(f" - {name} in {location}")

    if args.find_unsorted and cpp_only_unsorted:
        print("\nUnsorted classes/enums found in C++ files:")
        for name, location in cpp_only_unsorted:
            print(f" - {name} in {location}")

    cpp_files = []
    h_files = []
    for root, _, files in os.walk(SRC_DIR):
        for file in files:
            if file.endswith(('.cpp')):
                cpp_files.append(os.path.join(root, file))
            elif file.endswith(('.h', '.hpp')):
                h_files.append(os.path.join(root, file))
    
    print("Checking source files...")

    for cpp_path in cpp_files:
        if args.format:
            run_clang_format(cpp_path)

        with open(cpp_path, 'r', encoding='utf-8', errors='ignore') as f:
            original_content = f.read()

        # normalize line endings
        has_crlf = '\r\n' in original_content
        content_for_processing = original_content.replace('\r\n', '\n')

        common_checks = CommonChecks(content_for_processing, cpp_path, cpp_class_map, fix=args.fix, slow=args.slow)
        modified_content = common_checks.run()
        source_checks = SourceChecks(modified_content, cpp_path, cpp_class_map, fix=args.fix, slow=args.slow)
        modified_content = source_checks.run()

        # write fixes
        if args.fix and modified_content != content_for_processing:
            write_fixes(cpp_path, modified_content)

    print("Checking header files...")

    for h_path in h_files:
        if args.format:
            run_clang_format(h_path)

        with open(h_path, 'r', encoding='utf-8', errors='ignore') as f:
            original_content = f.read()

        # normalize line endings
        has_crlf = '\r\n' in original_content
        content_for_processing = original_content.replace('\r\n', '\n')

        common_checks = CommonChecks(content_for_processing, h_path, cpp_class_map, fix=args.fix, slow=args.slow)
        modified_content = common_checks.run()
        header_checks = HeaderChecks(modified_content, h_path, cpp_class_map, fix=args.fix, slow=args.slow)
        modified_content = header_checks.run()

        # write fixes
        if args.fix and modified_content != content_for_processing:
            write_fixes(h_path, modified_content)
    
    if args.fix:
        print("Automatic fixes completed. Please review the changes made.")

    if not args.slow:
        print("WARNING: Slow checks were not run, make sure you run them!")

    if issueFound:
        print("Formatting issues found.")
        exit(1)
    else:
        print("No issues found!")

if __name__ == "__main__":
    main()
