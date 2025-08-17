# Exports the .bss data to a CSV
#@author Boreal
#@category NX-Switch

import csv
import os

from ghidra.app.script import GhidraScript
from ghidra.program.model.symbol import SymbolType
from ghidra.program.model.address import AddressSet

# this is java.io.file
OutputFilePathObject = askFile("Save CSV file", "OK")
output_file_path = OutputFilePathObject.getAbsolutePath()

def is_valid_name(name: str) -> bool:
    return not name.startswith(("DAT_"))

listing = currentProgram().getListing()

def get_data_heads(block):
    start = block.getStart()
    end = block.getEnd()
    
    addr = start
    
    print(start)
    print(end)

if output_file_path:
    with open(output_file_path, 'w', newline='') as csvfile:
        fieldnames = ['Address', 'Name']
        csvwriter = csv.DictWriter(csvfile, fieldnames=fieldnames)

        bss = currentProgram().getMemory().getBlock(".bss")
        symbols = currentProgram().getSymbolTable().getSymbols(AddressSet(bss.getAddressRange()), SymbolType.LABEL, True)

        for data in symbols:
            csvwriter.writerow({
                'Address': f'0x{data.getAddress().getOffset():016x}',
                'Name': data.getName()
            })
        
    print(f"CSV file '{output_file_path}' has been generated.")
else:
    print("Operation cancelled by the user.")