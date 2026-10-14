import csv
import os
import sys

# gotta do this otherwise it won't find the util folder
common = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "common"))
sys.path.append(common)

from util import config

input = config.get_data_csv_path()
print(f"[INPUT] {input}")

import ida_kernwin
import idc
import idautils

with open(input, 'r', newline='') as f:
	reader = csv.DictReader(f)

	for row in reader:
		# print(row)
		
		if len(row) < 2:
			continue

		addr, name = row["Address"], row["Name"]

		if not addr or not name:
			continue

		try:
			address = int(addr, 16)
		except ValueError:
			print(f"[ERR] Invalid address str: {addr}", flush=True) # in what world would this ever happen???????
			continue

		seg = idc.get_segm_name(address)
		if seg != '.bss':
			continue

		cur_name = idc.get_name(address)
		if not cur_name:
			if idc.set_name(address, name, idc.SN_CHECK):
				print(f"[CREATE] -> {addr}: '{name}'", flush=True)
			else:
				print(f"[ERR] Failed to set name '{name}' at {addr}", flush=True)
		elif cur_name != name:
			if idc.set_name(address, name, idc.SN_CHECK):
				print(f"[RENAME] -> {addr}: '{cur_name}' -> '{name}'", flush=True)
			else:
				print(f"[ERR] Failed to rename '{cur_name}' at {addr} to '{name}'", flush=True)

print("[RENAME_DATA] Done!", flush=True)