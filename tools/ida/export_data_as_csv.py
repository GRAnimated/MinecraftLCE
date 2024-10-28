import csv
import ida_kernwin
import idc
import idautils

output_file_path = ida_kernwin.ask_file(1, "*.csv", "Save CSV file")

if output_file_path:
    with open(output_file_path, 'w', newline='') as csvfile:
        fieldnames = ['Address', 'Name']
        csvwriter = csv.DictWriter(csvfile, fieldnames=fieldnames)

        for seg_ea in idautils.Segments():
            seg_name = idc.get_segm_name(seg_ea)
            if seg_name == '.bss':
                for head in idautils.Heads(seg_ea, idc.get_segm_end(seg_ea)):
                    if idc.is_data(idc.get_full_flags(head)):
                        symbol_name = idc.get_name(head)
                        
                        if not symbol_name or symbol_name.startswith(("off_", "dword", "qword", "byte", "word", "algn", "stru")):
                            continue

                        csvwriter.writerow({
                            'Address': f'0x{head:016X}',
                            'Name': symbol_name
                        })

    print(f"CSV file '{output_file_path}' has been generated.")
else:
    print("Operation cancelled by the user.")
