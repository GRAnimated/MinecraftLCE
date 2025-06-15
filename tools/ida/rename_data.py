import csv
import ida_kernwin
import idc
import idautils

input_file_path = ida_kernwin.ask_file(0, "*.csv", "Select CSV file")

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
                address = int(address_str, 16)
            except ValueError:
                print(f"Invalid address format: {address_str}", flush=True)
                continue

            seg = idc.get_segm_name(address)
            if seg != '.bss':
                print(f"Address {address_str} not in .bss, skipping.", flush=True)
                continue

            # Attempt to rename
            current_name = idc.get_name(address)
            if not current_name:
                if idc.set_name(address, name, idc.SN_CHECK):
                    print(f"Added new name '{name}' at {address_str}", flush=True)
                else:
                    print(f"Failed to add name '{name}' at {address_str}", flush=True)
            elif current_name != name:
                if idc.set_name(address, name, idc.SN_CHECK):
                    print(f"Renamed '{current_name}' to '{name}' at {address_str}", flush=True)
                else:
                    print(f"Failed to rename '{current_name}' at {address_str} to '{name}'", flush=True)

    print("Renaming from CSV completed.", flush=True)
else:
    print("Operation cancelled by the user.", flush=True)
