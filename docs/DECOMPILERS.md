# Decompilers

## IDA Pro

1. Install `nxo64.py` from `reswitched/loaders`.  [Instructions](https://github.com/reswitched/loaders?tab=readme-ov-file#installation)
2. Open `ida64.exe` and disassemble `main.nso`.
3. To use scripts, click `File->Script File` and select the script you want to use.  

## Ghidra

### Setup Instructions

1. Setup [Ghidrathon](https://github.com/mandiant/Ghidrathon). Make sure `Ghidrathon` has access to the `toml` package.
2. Setup [Ghidra Switch Loader](https://github.com/Adubbz/Ghidra-Switch-Loader).
3. Create a new project. When importing `main.nso`, click `Options`. Then set `Base Address` to `0x7100000000`.
4. Open the `Script Manager` (green play icon) from Ghidra's toolbar.
5. Click on Manage Script Directories (bullet points icon) inside the Script Manager, and add `tools/ghidra`. Do not add `tools/common/ghidra_scripts`.
6. Select the `NX-Switch` category, and use the scripts provided. Information and instructions for each individual script are shown inside the Script Manager.
