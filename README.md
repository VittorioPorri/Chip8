# CHIP-8 Emulator

A CHIP-8 emulator written in **C++17** and **SDL2**. 
This project is built with a strict separation of concerns, dividing the hardware emulation core from the frontend (graphics and input) to ensure clean, maintainable, and platform-independent code.

## Project Structure
```text
.
├── CMakeLists.txt        # Build system configuration
├── README.md
└── src/
    ├── main.cpp          # Entry point and timing loop
    ├── core/
    │   ├── Chip8.hpp     # CPU core definitions
    │   └── Chip8.cpp     
    └── frontend/
        ├── Input.hpp     # Keyboard handling
        ├── Input.cpp
        ├── Renderer.hpp  # SDL2 Graphics handling (64x32 scaled)
        └── Renderer.cpp
```

## Requirements

To build and run this project, you need:

* A C++17 compiler (GCC)
* CMake
* SDL2 development libraries

## Building the Emulator

This project uses CMake for build automation.

> [!IMPORTANT]
> Do not build inside the source directory. Instead, use a dedicated build folder.

```bash
git clone https://github.com/VittorioPorri/Chip8
    
cd Chip8
    
mkdir build
cd build

cmake ..
make
```

## Usage

After compiling, the executable will be located in your `build` directory.
Run the emulator on the terminal by passing the path to a CHIP-8 ROM as an argument:

```bash
./chip8Emu path/to/your/rom.ch8
```

## Controls

The original CHIP-8 used a 16-key hexadecimal keypad (0-F). This emulator maps them to the left side of a modern standard keyboard:

| Original CHIP-8 Keypad | Modern Keyboard Mapping |
| --- | --- |
| `1` `2` `3` `C` | `1` `2` `3` `4` |
| `4` `5` `6` `D` | `Q` `W` `E` `R` |
| `7` `8` `9` `E` | `A` `S` `D` `F` |
| `A` `0` `B` `F` | `Z` `X` `C` `V` |
