# Minecraft: LCE Decompilation Project

![Progress](https://github.com/GRAnimated/MinecraftLCE-docs/blob/main/img/progress.png?raw=true)

[![Discord Channel][discord-badge]][discord]

[discord]: https://discord.gg/DEuS3feXED
[discord-badge]: https://img.shields.io/discord/1194500576122253312?color=%237289DA&logo=discord&logoColor=%23FFFFFF

WIP Decompilation of Minecraft: Nintendo Switch Edition v1.0.17.

**This repository does not contain game assets and cannot be used to play the game.**

## Resources
This project requires a `main` dumped from the latest *Minecraft: Nintendo Switch Edition* update, v1.0.17.

For porting symbols, its strongly recommended to get the `Minecraft.Client.rpx` from *Minecraft: Wii U Edition* Patch 35 (v560). Only basing things off of the base/latest update will hurt you in the long run.

Though 4J/Mojang/Microsoft has never taken action on dumps of the LCE games uploaded online, these executables will never be provided on the repo directly. They have taken down projects that have not been clean-room in their research, though. This includes the official Minecraft: Java Edition mappings, which are licensed by Microsoft, and cannot be used within the scope of this project.

## Why Nintendo Switch Edition?

Legacy Console Edition released for the Xbox 360, PS3, PS Vita, Wii U, Xbox One, PS4, and Nintendo Switch.

Wii U Edition is the only edition to contain function symbols. The decomp would work off of that version of the game, if it weren't for the compiler toolchain GHS being abysmal. The chance that we find a matching compiler version is next to none, so our assembly wouldn't be matching either way.

Nintendo Switch Edition on the other hand was compiled with Clang where it's easy enough to find the compiler version just by the release date of the game. The advantage here is that we're able to match the assembly 1:1, but Clang is also *much* more lenient compared to GHS. On old-gen platforms, LCE relied heavily on Boost, while on new-gen platforms it got replaced with standard library. We can still match the code without using the library's functions, but it wouldn't be a 1:1 match on most other platforms.

Without any symbols at all, this would make the Switch Edition pretty worthless on its own. With both editions of LCE open in IDA/Ghidra though, porting symbols is just a bad chore. Additionally, the Switch Edition does contain typeinfo, so vtables are already located for us.

The Nintendo Switch Edition release only lasted for a year, before being replaced with Minecraft Bedrock. This means that the LCE's life support was cut off early for current-gen users at the time, and did not receive Update Aquatic as other LCE ports did.

While the latest version of Nintendo Switch Edition is v1.0.17, that version only matches up with Wii U Edition's Patch 35 (v560). Wii U Edition would get a further 8 updates (up until v688) before LCE was abandoned for good.

## Building
See [BUILDING.md](docs/BUILDING.md).

## Contributing
See [CONTRIBUTING.md](docs/CONTRIBUTING.md).

---

Minecraft LCE Decompilation logo by [@break-core](https://github.com/break-core?tab=repositories)

This repository is based on the BOTW decomp ([zeldaret/botw](https://github.com/zeldaret/botw))

Building instructions based on the Super Mario Odyssey decomp ([MonsterDruide1/OdysseyDecomp](https://github.com/MonsterDruide1/OdysseyDecomp)).
