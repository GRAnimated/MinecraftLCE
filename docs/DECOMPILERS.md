# Decompilers

## IDA Pro
*TODO: Add IDA instructions*

## Ghidra
### Setup Instructions

1. Setup `Ghidrathon`. Instructions are available [here]https://github.com/mandiant/Ghidrathon#installing-ghidrathon). Make sure `Ghidrathon` has access to the `toml` package.
2. Create a new project. When importing `main.elf`, click `Options`. Then set `Image Base` to `0x7100000000`. Do not run analysis.
3. Open the `Script Manager` (green play icon) from Ghidra's toolbar.
4. Click on Manage Script Directories (bullet points icon) inside the Script Manager, and add `tools/ghidra`. Do not add `tools/common/ghidra_scripts`.
5. Select the `NX-Switch` category, and use the scripts provided. Information and instructions for each individual script are shown inside the Script Manager.