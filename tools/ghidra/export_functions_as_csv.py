# !!!UNTESTED!!!
#@author Boreal
#@category NX-Switch

import csv
import os

from ghidra.app.script import GhidraScript

# this is java.io.file
OutputFilePathObject = askFile("Select the CSV file to update, checked functions will be preserved", "OK")
output_file_path = OutputFilePathObject.getAbsolutePath()

def is_valid_name(name: str) -> bool:
    return not name.startswith(("sub_", "nullsub_", "j_", "FUN_", "thunk_FUN_"))

# Load the existing csv if it exists
existing_data = {}
if output_file_path and os.path.exists(output_file_path):
    with open(output_file_path, 'r', newline='') as csvfile:
        reader = csv.DictReader(csvfile)
        for row in reader:
            address = row['Address']
            existing_data[address] = row

if output_file_path:
    with open(output_file_path, 'w', newline='') as csvfile:
        fieldnames = ['Address', 'Quality', 'Size', 'Name']
        csvwriter = csv.DictWriter(csvfile, fieldnames=fieldnames)
        csvwriter.writeheader()

        for func in currentProgram().getListing().getFunctions(True):
            func_name = func.getName() 
            func_size = func.getBody().getNumAddresses()
            address   = func.getEntryPoint().toString(False, 16)

            quality = existing_data.get(address, {}).get('Quality', 'U')

            csvwriter.writerow({
                'Address': address,
                'Quality': quality,
                'Size': str(func_size).zfill(6),
                'Name': func_name if is_valid_name(func_name) else ''
            })

    print(f"CSV file '{output_file_path}' has been updated.")
else:
    print("Operation cancelled by the user.")

