# welcome to easy-discord-presence !

A lightweight Rich Presence app written in pure C (Win32 handles & Unix sockets) featuring a clean CLI interface.

It detects currently running processes and active window titles to automatically update your Discord status.

## Features
- Lightweight with zero heavy runtime dependencies.
- Automatic process/window detection.
- Multiplatform architecture:
  - Windows: Fully supported via Win32 API.
  - Unix systems (Linux / MacOS) : In active development <(＿ ＿)>

## Installation

### Pre-compiled binaries
Check the [Releases](releases) tab (～￣▽￣)～

### Building from source

**Prerequisites:**
- GCC / MinGW (recommended on Windows: [w64devkit](https://github.com/skeeto/w64devkit))
- Make

```bash
git clone [https://codeberg.org/adiyn/dis-rpC.git](https://codeberg.org/adiyn/dis-rpC.git)
cd dis-rpC
make
