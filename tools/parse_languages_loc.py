import argparse
import struct
import ctypes
import re

# Based on Boreal's excellent docs on the LOC file format at:
# https://github.com/boreals-back-again/Documentation/blob/main/LCE/File%20Types/LOC.md

class Reader:
    def __init__(self, data: bytes):
        self.data = data
        self.offset = 0
    
    def read(self, size: int):
        data = self.data[self.offset:self.offset+size]
        self.offset += size
        return data
    
    def read_uint(self):
        value = struct.unpack(">I", self.read(4))[0]
        return value
    
    def read_string(self, length: int):
        value = self.read(length).decode("utf-8")
        return value
    
    def read_bool(self):
        value = struct.unpack(">B", self.read(1))[0]
        return bool(value)
    
    def read_short(self):
        value = struct.unpack(">H", self.read(2))[0]
        return value
    
    def read_ushort(self):
        value = struct.unpack(">H", self.read(2))[0]
        return value
    
    def read_uint_array(self, count: int):
        values = []
        for _ in range(count):
            values.append(self.read_uint())
        return values
    
    def read_short_string_array(self, count: int):
        values = []
        for _ in range(count):
            length = self.read_ushort()
            values.append(self.read_string(length))
        return values

class LOCLanguageListEntry:
    language_code_length: ctypes.c_ushort
    language_code: str # Contains the ISO 639-1 code for the language.
    language_id = ctypes.c_uint

    def read(self, reader: Reader):
        self.language_code_length = reader.read_ushort()
        self.language_code = reader.read_string(self.language_code_length)
        self.language_id = reader.read_uint()

class LOCLanguageList:
    entries: list

    def read(self, reader: Reader, count: int):
        self.entries = []
        for _ in range(count):
            entry = LOCLanguageListEntry()
            entry.read(reader)
            self.entries.append(entry)

class LOCLanguageTableEntry:
    unknown_0 = ctypes.c_uint
    unknown_1 = bool
    language_code_length = ctypes.c_ushort
    language_code = str
    strings_count = ctypes.c_uint
    strings = list

    def read(self, reader: Reader):
        self.unknown_0 = reader.read_uint()
        self.unknown_1 = reader.read_bool()
        self.language_code_length = reader.read_ushort()
        self.language_code = reader.read_string(self.language_code_length)
        self.strings_count = reader.read_uint()
        self.strings = reader.read_short_string_array(self.strings_count)

class LOCLanguageTable:
    entries: list

    def read(self, reader: Reader, count: int):
        self.entries = []
        for _ in range(count):
            entry = LOCLanguageTableEntry()
            entry.read(reader)
            self.entries.append(entry)

class LOCKeyTable:
    use_unique_ids: bool
    key_count: ctypes.c_uint
    keys: list

    def read(self, reader: Reader):
        self.use_unique_ids = reader.read_bool()
        self.key_count = reader.read_uint()
        self.keys = reader.read_uint_array(self.key_count)

used_names = {}

class LOCFile:
    version: ctypes.c_uint
    language_count = ctypes.c_uint
    key_table: LOCKeyTable
    language_list: LOCLanguageList
    language_table: LOCLanguageTable

    def read(self, reader: Reader):
        self.version = reader.read_uint()
        self.language_count = reader.read_uint()
        self.key_table = LOCKeyTable()
        self.key_table.read(reader)

        self.language_list = LOCLanguageList()
        self.language_list.read(reader, self.language_count)

        self.language_table = LOCLanguageTable()
        self.language_table.read(reader, self.language_count)

    # Takes a string and makes a valid variable name for it
    def createNameFromString(self, string: str):
        final_str = ""

        words = re.findall(r"[A-Za-z0-9]+", string)

        # this name is very long, lets try to shorten it a bit
        if len(string) > 50:
            words = words[0:8]

        for i in range(len(words)):
            words[i] = words[i].capitalize()

        base_name = "".join(words) or "Unnamed" # if the string is empty
        
        # place an underscore behind numbers at the start of a string
        if len(base_name) > 0 and base_name[0].isnumeric():
            base_name = "_" + base_name

        if base_name not in used_names:
            used_names[base_name] = [string]
            return base_name
        
        existing_list = used_names[base_name]

        first_words = re.findall(r"[A-Za-z0-9]+", existing_list[0])
        new_words = re.findall(r"[A-Za-z0-9]+", string)

        diff = [w.capitalize() for w in new_words if w not in first_words]

        # find the first 5 words that are different
        if diff:
            name = f"{base_name}{''.join(diff[:5])}"
        else:
            name = f"{base_name}_{len(existing_list)}"

        used_names[base_name].append(string) # to count duplicates
        
        suffix_count = 1
        unique_name = name
        while unique_name in used_names:
            unique_name = f"{name}_{suffix_count}"
            suffix_count += 1
        
        used_names.setdefault(unique_name, [])
        used_names[unique_name].append(string)
        
        return unique_name

    def stringReplacements(self, string: str):
        # some things that we can shorten
        string = re.sub(r"Minecraft: .* Edition", "Console", string)
        string = string.replace("n't", "nt") # can't -> nt
        string = string.replace(" the", "")
        string = string.replace(" the", "")
        string = string.replace("  ", " ") # double spaces

        # confirm messages
        string = string.replace("Are you sure you want to ", "")
        return string

    def sanitizeString(self, string: str):
        string = string.replace("\n",r"\n").replace("\r",r"\r").replace("\t",r"\t")
        
        return string

    def createHeader(self, filename: str):
        with open(filename, 'w') as f:
            f.write('#pragma once\n\n')
            f.write('#include "types.h"\n\n')
            f.write('// clang-format off\n\n')
            f.write('namespace StringIDs {\n')

            for index, entry in enumerate(self.language_table.entries):
                if self.language_table.entries[index].language_code == "en-EN":
                    for i, string in enumerate(entry.strings):
                        name_id = self.key_table.keys[i]
                        name_id_str = f"{name_id:0{8}x}".upper()
                        
                        string = self.sanitizeString(string)
                        
                        comment = f"// {string[0:100]}{"..." if len(string) > 100 else ""}"

                        string = self.stringReplacements(string)

                        f.write(f'    constexpr u32 {self.createNameFromString(string)} = 0x{name_id_str}; {comment}\n')
            
            f.write('}\n')

def main(): 
    parser = argparse.ArgumentParser(description="Parse a LCE languages.loc")

    parser.add_argument(
        "input",
        type=argparse.FileType("rb"),
        help="The languages.loc file to parse"
    )
    
    parser.add_argument(
        "--create-header",
        nargs='?',
        default=None,
        const='StringIDs.h'
    )

    args = parser.parse_args()

    if args.input is None:
        parser.print_help()
        exit(1)

    with args.input as f:
        reader = Reader(f.read())
        loc = LOCFile()
        loc.read(reader)

        if args.create_header:
            loc.createHeader(args.create_header)

        # TODO: provide useful output
        print("Done!")
        print("Language count:", loc.language_count)
        print("Key count:", len(loc.key_table.keys))
        print("String count:", len(loc.language_table.entries[0].strings))

if __name__ == "__main__":
    main()
