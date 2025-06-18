# Renames data to those from the CSV
#@author Boreal
#@category NX-Switch

import csv
import os

from ghidra.app.script import GhidraScript
from ghidra.program.model.symbol import SourceType

# this is java.io.file
InputFilePathObject = askFile("Import from CSV file", "OK")
input_file_path = InputFilePathObject.getAbsolutePath()

if input_file_path:
    with open(input_file_path, 'r', newline='') as csvfile:
        csvreader = csv.reader(csvfile)

        print(csvfile)

        for row in csvreader:
            if len(row) < 2:
                continue

            address_str, name = row[0], row[1]

            if not address_str or not name:
                continue

            try:
                address = toAddr(int(address_str, 16))
            except ValueError:
                print(f"Invalid address format: {address_str}")
                continue
            
            data = getDataAt(address)

            if data is not None:
                data.getPrimarySymbol().setName(name, SourceType.USER_DEFINED)