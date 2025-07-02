import os
import re
import json
import yaml

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

                        # all sources we care about are either in Minecraft.Client or Minecraft.World
                        rel_path = rel_path.replace("Minecraft.Client/", "").replace("Minecraft.World/", "")

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

    for class_name, expected_path in expected_classes:
        cpp_location = cpp_map.get(class_name)
        #if not cpp_location:
        #    mismatches.append((class_name, "Missing in C++"))
        #else:
        if cpp_location:
            cpp_location_norm = cpp_location.replace("\\", "/")
            if expected_path not in cpp_location_norm:
                mismatches.append((class_name, f"Expected in '{expected_path}', found in '{cpp_location_norm}'"))
    return mismatches

def main():
    cpp_class_map = find_cpp_classes(SRC_DIR)
    nested_class_map = load_class_map_yaml("data/java_class_map.yaml")

    mismatches = compare_class_locations(cpp_class_map, nested_class_map)
    
    if not mismatches:
        print("All classes/enums are in expected locations.")
    else:
        print("Mismatches found:")
        for name, issue in mismatches:
            print(f" - {name}: {issue}")

if __name__ == "__main__":
    main()
