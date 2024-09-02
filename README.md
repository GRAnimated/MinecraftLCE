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

Nintendo Switch Edition on the other hand was compiled with Clang where it's easy enough to find the compiler version just by the release date of the game. The advantage here is that we're able to match the assembly 1:1, but Clang is also *much* more lenient compared to GHS. LCE used `boost` throughout the code pretty heavily, and while its asserts are visible in the Wii U release, they are nonexistent in the Switch release. We can still match the code without using the library's functions, but it wouldn't be a 1:1 match on most other platforms.

Without any symbols at all, this would make the Switch Edition pretty worthless on its own. With both editions of LCE open in IDA/Ghidra though, porting symbols is just a bad chore. Additionally, the Switch Edition does contain typeinfo, so vtables are already located for us.

The Nintendo Switch Edition release only lasted for a year, before being replaced with Minecraft Bedrock. This means that the LCE's life support was cut off early for current-gen users at the time, and did not receive Update Aquatic as other LCE ports did.

While the latest version of Nintendo Switch Edition is v1.0.17, that version only matches up with Wii U Edition's Patch 35 (v560). Wii U Edition would get a further 8 updates (up until v688) before LCE was abandoned for good.

## Building
The decomp toolchain was created for Linux & MacOS users. While it isn't a hard requirement, if you're running Windows its advised that you [setup WSL](https://learn.microsoft.com/en-us/windows/wsl/install) with an Ubuntu-like distro for the easiest setup.

The instructions below assume you're running a form of Linux (WSL or native).

### 1. Set up dependencies

* Python 3.6 or newer with [pip](https://pip.pypa.io/en/stable/installation/)
* Ninja
* CMake 3.13+
    * If you are on Ubuntu 18.04, you must first [update CMake by using the official CMake APT repository](https://apt.kitware.com/).
* ccache (to speed up builds)
* xdelta3
* clang (for compiling Rust tools)

Ubuntu users can install those dependencies by running:

```shell
sudo apt install python3 ninja-build cmake ccache xdelta3 clang libssl-dev libncurses5
```

Additionally, you'll also need:

* A Rust toolchain ([follow the instructions here](https://www.rust-lang.org/tools/install))
* The following Python modules: `capstone colorama cxxfilt pyelftools ansiwrap watchdog python-Levenshtein toml` (install them with `pip install ...`)

### 2. Set up the project

1. Clone this repository. If you are using WSL, please clone the repo *inside* WSL, *not* on the Windows side (for performance reasons).

2. Run `git submodule update --init --recursive`

    Next, you'll need to acquire the **original v1.0.17 `main` NSO executable**.

3. Run `tools/setup.py [path to the NSO]`
    * This will:
        * install tools/check to check for differences in decompiled code
        * convert the executable if necessary
        * set up [Clang 5.0.1](https://releases.llvm.org/download.html#5.0.1) by downloading it from the official LLVM website
        * create a build directory in `build/`
    * If something goes wrong, follow the instructions given to you by the script.
    * If you wish to use a CMake generator that isn't Ninja, use `--cmake_backend` to specify it.

### 3. Build

To start the build, just run

```shell
ninja -C build
```

By default, a multithreaded build is performed.

To check whether everything built correctly, just run `tools/check` after the build completes.

## Contributing
As this project is in its very early stages, its hard to put guidelines on something that will evolve over time as contributors gain a better understanding of the game's internals.

While almost all source paths aren't known, a few .cpp file names do appear in the Wii U Edition's global static constructors, along with a couple asserts giving file paths. Follow these file names wherever possible.

Another point of reference is the Switch Edition, showing us the file path to `Minecraft.World/Calendar.cpp` and some other files in that folder. World generation should be stored in this folder based on `MinecraftWorld_RunStaticCtors` routing all worldgen static constructors inside of the folder.

For another point of reference, you could also look at [the Minecraft: Pocket Edition decompilation](https://github.com/MCPE-RE/0.1.3j-core) for more inspiration. As a matter of fact, a lot of classes from that decompilation project share function names with this game's symbols. Both editions originated from Notch's messy Minecraft beta code, so it's no wonder that a lot of names were probably copied from Mojang's official mappings at the time.

##

This repository is based on the BOTW decomp ([zeldaret/botw](https://github.com/zeldaret/botw)), with building instructions based on the Super Mario Odyssey decomp ([MonsterDruide1/OdysseyDecomp](https://github.com/MonsterDruide1/OdysseyDecomp)).
