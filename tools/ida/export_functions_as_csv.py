import csv
import ida_kernwin
import idc

output_file_path = ida_kernwin.ask_file(1, "*.csv", "Save CSV file")

def is_valid_name(name: str) -> bool:
    return not name.startswith(("sub_", "nullsub_", "j_"))

if output_file_path:
    with open(output_file_path, 'w', newline='') as csvfile:
        fieldnames = ['Address', 'Quality', 'Size', 'Name']

        csvwriter = csv.DictWriter(csvfile, fieldnames=fieldnames)

        csvwriter.writeheader()

        for func_addr in Functions():
            func_name = idc.get_func_name(func_addr)
            func_size = idc.get_func_attr(func_addr, FUNCATTR_END) - func_addr

            csvwriter.writerow({
                'Address': f'0x{hex(func_addr)[2:].zfill(16)}',
                'Quality': 'U',
                'Size': str(func_size).zfill(6),
                'Name': func_name if is_valid_name(func_name) else ''
            })

    print(f"CSV file '{output_file_path}' has been generated.")
else:
    print("Operation cancelled by the user.")
