import csv
import ida_kernwin
import idc
import idautils
import os

# TODO later I can probably write some compat classes so this script will run on Ghidra as well. -Dexrn

common = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "common"))
sys.path.append(common)

from util import config

output = config.get_data_csv_path()
if not output:
	output = ida_kernwin.ask_file(1, "*.csv", "Choose a path to write the CSV file to")

print(f"[OUTPUT] {output}")

f = ['Address', 'Name']
existing_data = {}
if output and os.path.exists(output):
    with open(output, 'r', newline='') as csv:
        reader = csv.DictReader(csv)
        
        for row in reader:
            if len(row) >= 2:
                addr, name = row["Address"], row["Name"]
                existing_data[addr] = name

if output:
    seg = idaapi.get_segm_by_name(".bss")

    start = seg.start_ea
    end   = seg.end_ea

    for ea, sym in idautils.Names():
        if start <= ea < end:
            if not sym:
                continue
            
            addr = f'0x{ea:016X}'
            existing_data[addr] = sym

    with open(output, 'w', newline='') as csv:
        writer = csv.DictWriter(csv, fieldnames=f)
        writer.writeheader()
	
        for addr, name in sorted(existing_data.items(), key=lambda item: int(item[0], 16)):
            writer.writerow({
                'Address': addr,
                'Name': name
            })

    print("[EXPORT_DATA] Done!")
else:
    print("[EXPORT_DATA] Cancelled.")
