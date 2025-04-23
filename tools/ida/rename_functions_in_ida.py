# Renames functions in an IDA database to match the function names
# in the decompiled source code

# TODO: PR this to upstream!!! This is modified to create functions that don't already exist

import csv
import idc
import ida_funcs
import os
from util import config

csv_path = config.get_functions_csv_path()

def can_overwrite_name(addr: int, new_name: str):
    if not new_name or new_name.startswith(("sub_", "nullsub_", "j_")):
        return False

    # old_name: str = idc.get_name(addr)
    # if not old_name:
    #     return True
# 
    # if old_name.startswith(("sub_", "nullsub_", "j_")):
    #     return True
# 
    # if old_name.startswith("_Z"):
    #     return True
# 
    # if new_name.startswith("_Z"):
    #     return True

    return True # we have to allow wii u symbols

with open(csv_path, "r") as f:
    reader = csv.reader(f)
    next(reader)

    for fn in reader:
        addr = int(fn[0], 16)
        name = fn[3]

        if ida_funcs.get_func(addr) is None:
            print(f"Creating function at {hex(addr)} with name {name}")
            ida_funcs.add_func(addr)

        if can_overwrite_name(addr, name):
            idc.set_name(addr, name, idc.SN_CHECK | idc.SN_NOWARN)
