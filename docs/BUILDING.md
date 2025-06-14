# Building
The decomp toolchain was created for Linux & MacOS users. While it isn't a hard requirement, if you're running Windows its advised that you [setup WSL](https://learn.microsoft.com/en-us/windows/wsl/install) with an Ubuntu-like distro for the easiest setup.

The instructions below assume you're running a form of Linux (WSL or native).

## 1. Set up dependencies

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

## 2. Set up the project

1. Clone this repository. If you are using WSL, please clone the repo *inside* WSL, *not* on the Windows side (for performance reasons).

2. Run `git submodule update --init --recursive`

    Next, you'll need to acquire the **original v1.0.17 `main` NSO executable**.

3. Run `tools/setup.py [path to the NSO]`
    * This will:
        * install tools/check to check for differences in decompiled code
        * convert the executable if necessary
        * set up [Clang 4.0.1](https://releases.llvm.org/download.html#4.0.1) by downloading it from the official LLVM website
        * create a build directory in `build/`
    * If something goes wrong, follow the instructions given to you by the script.
    * If you wish to use a CMake generator that isn't Ninja, use `--cmake_backend` to specify it.

## 3. Build

To start the build, just run

```shell
ninja -C build
```

By default, a multithreaded build is performed.

To check whether everything built correctly, just run `tools/check` after the build completes.

## 4. Decompilers

For instructions on setting up a decompiler, see [DECOMPILERS.md](DECOMPILERS.md).