# !!!UNTESTED!!!
#@author Boreal
#@category NX-Switch

import csv
import os

from ghidra.app.script import GhidraScript
from ghidra.program.model.symbol import SourceType
from ghidra.program.model.address import AddressSet

common_path = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "common"))

# util collides with java.util so this has to be done
import importlib
config_path = os.path.join(common_path, "util/config.py")
spec = importlib.util.spec_from_file_location("config", config_path)
config = importlib.util.module_from_spec(spec)
spec.loader.exec_module(config)

csv_path = config.get_functions_csv_path()

function_manager = currentProgram().getFunctionManager()

def can_overwrite_name(new_name: str):
    if not new_name or new_name.startswith(("sub_", "nullsub_", "j_")):
        return False

    return True # we have to allow wii u symbols

def delete_multichunk_funcs():
    for func in function_manager.getFunctions(True):
        if func.getBody().getNumAddressRanges() > 1:
            function_manager.removeFunction(func.getEntryPoint())

delete_multichunk_funcs()

with open(csv_path, "r") as f:
    reader = csv.reader(f)
    next(reader)

    prev_func = None

    for fn in reader:
        addr = toAddr(fn[0])
        size = int(fn[2])
        name = fn[3]

        func = function_manager.getFunctionAt(addr)

        if func is None:
            print(f"Creating function at {addr} with name {name}")
            func = function_manager.createFunction(None, addr, AddressSet(addr, addr.add(size - 1)), SourceType.USER_DEFINED)
        
        elif func.getEntryPoint() != addr:
            print(f"Fixing function at {addr} with name {name}")
            prev_func.setBody(AddressSet(prev_func.getEntryPoint(), func.getBody().getMaxAddress().add(1)))
            func = function_manager.createFunction(None, addr, AddressSet(addr, addr.add(size - 1)), SourceType.USER_DEFINED)

        if can_overwrite_name(name):
            func.setName(name, SourceType.USER_DEFINED)
            
        prev_func = func
    print("Renaming from functions completed.")