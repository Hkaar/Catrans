# Catrans

[![GitHub license](https://badgen.net/github/license/Hkaar/Catrans)](https://github.com/Hkaar/Catrans/blob/main/LICENSE)
[![GitHub release](https://img.shields.io/github/release/Hkaar/Catrans.svg)](https://GitHub.com/Hkaar/Catrans/releases/)

Catrans is a simple terminal based cash register, it's main purpose is to record
and process transactions by the terminal.

## Features

- Able to record up to more than 99+ items per-cart
- Configurable
- Easy to use & setup

## Requirements

- GCC/MSVC/Clang
- CMake >= 3.12

## Setup guide

Clone the project

```bash
git clone https://github.com/Hkaar/Catrans.git
```

Create the build directory

`bash`

```bash
mkdir build
```

`PowerShell`

```powershell
New-Item -Path "." -Name "build" -ItemType Directory
```

Configure CMake

`bash`

```bash
cd build && cmake ..
```

`PowerShell`

```powershell
cd build; cmake ..
```

Build the project

```bash
cmake --build build
```

Run the project

```bash
./build/catrans
```
