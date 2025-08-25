import csv
import ida_kernwin
import idc
import idautils
import os

output_file_path = ida_kernwin.ask_file(1, "*.csv", "Save CSV file")

# Load the existing csv if it exists
existing_data = {}
if output_file_path and os.path.exists(output_file_path):
    with open(output_file_path, 'r', newline='') as csvfile:
        reader = csv.reader(csvfile)
        for row in reader:
            if len(row) >= 2:
                address, name = row[0], row[1]
                existing_data[address] = {"Address": address, "Name": name}

if output_file_path:
    seg = idaapi.get_segm_by_name(".bss")

    start = seg.start_ea
    end   = seg.end_ea

    for ea, symbol_name in idautils.Names():
        if start <= ea < end:
            if not symbol_name:
                continue
            
            address = f'0x{ea:016X}'

            existing_data[address] = {"Address": address, "Name": symbol_name}

    # Write merged results back
    with open(output_file_path, 'w', newline='') as csvfile:
        csvwriter = csv.writer(csvfile)
        
        for address, row in sorted(existing_data.items(), key=lambda item: int(item[0], 16)):
            csvwriter.writerow([row["Address"], row["Name"]])

    print(f"CSV file '{output_file_path}' has been generated.")
else:
    print("Operation cancelled by the user.")
