import csv
import ida_kernwin
import idc
import os

common = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "common"))
sys.path.append(common)

from util import config

output = config.get_data_csv_path()
if not output:
	output = ida_kernwin.ask_file(1, "*.csv", "Choose a path to write the CSV file to")

print(f"[OUTPUT] {output}")

def is_valid_name(name: str) -> bool:
    return not name.startswith(("sub_", "nullsub_", "j_"))


fieldnames = ['Address', 'Quality', 'Size', 'Name']
existing_data = {}
if output and os.path.exists(output):
    with open(output, 'r', newline='') as csvfile:
		
        reader = csv.DictReader(csvfile)
        for row in reader:
            address = row['Address']
            existing_data[address] = row

if output:
    with open(output, 'w', newline='') as csvfile:        
        csvwriter = csv.DictWriter(csvfile, fieldnames=fieldnames)
        csvwriter.writeheader()

        for func_addr in Functions():
            func_name = idc.get_func_name(func_addr)
            func_size = idc.get_func_attr(func_addr, FUNCATTR_END) - func_addr
            address = f'0x{hex(func_addr)[2:].zfill(16)}'

            quality = existing_data.get(address, {}).get('Quality', 'U')

            csvwriter.writerow({
                'Address': address,
                'Quality': quality,
                'Size': str(func_size).zfill(6),
                'Name': func_name if is_valid_name(func_name) else ''
            })

    print("[EXPORT_FUNCTIONS] Done!")
else:
    print("[EXPORT_FUNCTIONS] Cancelled.")
