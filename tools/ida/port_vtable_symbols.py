import idc
import ida_name
import ida_kernwin

rename_these = [

]

def find_vtable(symbol):
    # Form the vtable name
    vtable_name = "_ZTV" + str(len(symbol)) + symbol

    # Search for the vtable symbol in the database
    vtable_ea = idc.get_name_ea_simple(vtable_name)
    if vtable_ea != idc.BADADDR:
        return vtable_ea
    else:
        print(f"Vtable {vtable_name} not found!")
        return None

def fill_vtable_arrays(vtable_ea, derived):
    base_vtable_names = []
    derived_vtable_addresses = []

    if vtable_ea is None:
        return

    # Iterate over the functions in the vtable and print their names
    current_ea = vtable_ea + 16
    current_vtable_offset = 8
    
    while True:
        name = ida_name.get_name(current_ea + current_vtable_offset)

        if name:
            break

        if not derived:
            qword = idc.get_qword(current_ea + current_vtable_offset)
            qword_name = ida_name.get_name(qword)
            if not qword_name:
                break
            
            base_vtable_names.append(qword_name)
        if derived:
            derived_vtable_addresses.append(current_ea + current_vtable_offset)

        current_vtable_offset += 8
    
    if derived:
        return derived_vtable_addresses
    else:
        return base_vtable_names

def rename_base_vtable_class(names, new_class):
    new_names = []
    for name in names:
        parts = re.split(r'(_ZNK|_ZN)(\d+)([a-zA-Z]+)', name)
        if len(parts) == 5:  # Check if the split was successful
            new_name = f"{parts[1]}{str(len(new_class))}{new_class}{parts[4]}"
            new_names.append(new_name)
        else:
            # If the split was not successful, keep the original name
            new_names.append(name)
    return new_names

def replace_derived_names(new_names, addresses):
    index = 0
    for address in addresses:
        if index >= len(new_names):
            break

        current_qword = idc.get_qword(address)
        current_qword_name = ida_name.get_name(current_qword)

        if current_qword_name.startswith("sub_") or current_qword_name.startswith("nullsub"):
            ida_name.set_name(current_qword, new_names[index])
            print(ida_name.get_name(current_qword))
        index += 1


#def main():
#    # Get the symbol inputs
#    #base_symbol = ida_kernwin.ask_str("Block", 0, "Enter the base symbol:")
#    #derived_symbol = ida_kernwin.ask_str("AnvilBlock", 0, "Enter the derived symbol:")
#
#    base_symbol = "Block"
#
#    for derived_symbol in rename_these:
#        # Find vtables for both symbols
#        base_vtable = find_vtable(base_symbol)
#        derived_vtable = find_vtable(derived_symbol)
#
#        # Print functions in both vtables
#        if base_vtable and derived_vtable:
#            base_vtable_names = fill_vtable_arrays(base_vtable, False)
#            derived_vtable_addresses = fill_vtable_arrays(derived_vtable, True)
#
#            #print(rename_base_vtable_class(base_vtable_names, derived_symbol))
#            #print(derived_vtable_addresses)
#
#            replace_derived_names(rename_base_vtable_class(base_vtable_names, derived_symbol), derived_vtable_addresses)

def main():
    # Get the symbol inputs
    base_symbol = ida_kernwin.ask_str("Block", 0, "Enter the base symbol:")
    derived_symbol = ida_kernwin.ask_str("AnvilBlock", 0, "Enter the derived symbol:")

    # Find vtables for both symbols
    base_vtable = find_vtable(base_symbol)
    derived_vtable = find_vtable(derived_symbol)

    # Print functions in both vtables
    if base_vtable and derived_vtable:
        base_vtable_names = fill_vtable_arrays(base_vtable, False)
        derived_vtable_addresses = fill_vtable_arrays(derived_vtable, True)

        #print(rename_base_vtable_class(base_vtable_names, derived_symbol))
        #print(derived_vtable_addresses)
        
        replace_derived_names(rename_base_vtable_class(base_vtable_names, derived_symbol), derived_vtable_addresses)

if __name__ == "__main__":
    main()
