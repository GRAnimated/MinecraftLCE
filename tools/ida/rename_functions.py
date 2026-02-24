# Renames functions in an IDA database to match the function names
# in the decompiled source code

import csv
import idc
import ida_funcs
import ida_range
import ida_auto
import idautils
import idaapi
import ida_hexrays
import os
import sys

# import IDA 9 modules if possible
try:
    import ida_ida
    USE_NEW_API = True
except ImportError:
    USE_NEW_API = False

common_path = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "common"))
sys.path.append(common_path)

from util import config

csv_path = config.get_functions_csv_path()

def get_min_ea():
    return ida_ida.inf_get_min_ea() if USE_NEW_API else idaapi.cvar.inf.min_ea

def get_max_ea():
    return ida_ida.inf_get_max_ea() if USE_NEW_API else idaapi.cvar.inf.max_ea

def iter_all_funcs():
    for func_ea in idautils.Functions(get_min_ea(), get_max_ea()):
        yield idaapi.get_func(func_ea)

def iter_multichunk_funcs():
    for func_t in iter_all_funcs():
        if func_t and func_t.tailqty > 0:
            yield func_t

def delete_multichunk_funcs():
    for func_t in iter_multichunk_funcs():
        idaapi.del_func(func_t.start_ea)

def can_overwrite_name(addr: int, new_name: str):
    if not new_name or new_name.startswith(("sub_", "nullsub_", "j_")):
        return False
    return True # we have to allow wii u symbols

delete_multichunk_funcs()

with open(csv_path, "r") as f:
    reader = csv.reader(f)
    next(reader)

    prev_addr = 0
    prev_size = 0

    for fn in reader:
        addr = int(fn[0], 16)
        progress = fn[1]
        size = int(fn[2])
        name = fn[3]

        func = ida_funcs.get_func(addr)

        if func is None:
            print(f"[CREATE] -> {hex(addr)}: {name}")
            ida_funcs.add_func(addr)
            ida_funcs.set_func_end(addr, addr + size)
        elif func.start_ea != addr:
            print(f"[FIX] -> {hex(addr)}: {name}")
            ida_funcs.set_func_end(prev_addr, prev_addr + prev_size)
            ida_funcs.add_func(addr)
            ida_funcs.set_func_end(addr, addr + size)

        if can_overwrite_name(addr, name):
            idc.set_name(addr, name, idc.SN_CHECK | idc.SN_NOWARN)

        if progress == "O":
            idc.set_color(addr, idc.CIC_FUNC, 0x276e20)

        prev_addr = addr
        prev_size = size

print("[RENAME_FUNCTIONS] Done!")
