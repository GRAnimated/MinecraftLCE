# Decompilers

## IDA Pro
*TODO: Add IDA instructions*

## Ghidra
### Setup Instructions

1. Setup `Ghidrathon`. Instructions are available [here]https://github.com/mandiant/Ghidrathon#installing-ghidrathon). Make sure `Ghidrathon` has access to the `toml` package.
2. Create a new project, and add the `main.elf` binary to it. Do not run analysis. 
3. Set the image base with `Window -> Memory map -> Set Image Base (house icon)` to `0x7100000000`
4. Open the `Script Manager` (green play icon) from Ghidra's toolbar.
5. Click on Manage Script Directories (bullet points icon) inside the Script Manager, and add `tools/ghidra`. Do not add `tools/common/ghidra_scripts`.
6. Select the `NX-Switch` category, and use the scripts provided. Information and instructions for each individual script are shown inside the Script Manager.