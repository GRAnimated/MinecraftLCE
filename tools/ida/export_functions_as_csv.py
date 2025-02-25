import ida_idaapi
import idc
import ida_kernwin
import idautils
import csv

def export_functions_as_csv():
    output_file_path = ida_kernwin.ask_file(1, "*.csv", "Save CSV file")

    if output_file_path:
        with open(output_file_path, 'w', newline='') as csvfile:
            fieldnames = ['Address', 'Quality', 'Size', 'Name']

            csvwriter = csv.DictWriter(csvfile, fieldnames=fieldnames)

            csvwriter.writeheader()

            for func_addr in idautils.Functions():
                func_name = idc.get_func_name(func_addr)
                func_size = idc.get_func_attr(func_addr, idc.FUNCATTR_END) - func_addr

                csvwriter.writerow({
                    'Address': f'0x{func_addr:016X}',
                    'Quality': 'U',
                    'Size': f'{func_size:06}',
                    'Name': func_name
                })

        print(f"CSV file '{output_file_path}' has been generated.")
    else:
        print("Operation cancelled by the user.")

class IDA_export_functions_as_csv(ida_idaapi.plugin_t):
    flags = 0
    comment = "Export functions as CSV"
    help = "Export functions as CSV"
    wanted_name = "Export functions as CSV"
    wanted_hotkey = ""

    def init(self):
        return ida_idaapi.PLUGIN_OK

    def run(self, arg):
        export_functions_as_csv()

    def term(self):
        pass

def PLUGIN_ENTRY():
    return IDA_export_functions_as_csv()