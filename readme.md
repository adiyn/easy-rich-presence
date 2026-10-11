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
git clone https://github.com/adiyn/easy-rich-presence
cd easy-rich-presence
make
```
## Roadmap

    [ ] Complete native Linux/Unix socket implementation
    [ ] Config file support for custom app rules
    [ ] Go outside

## License

Distributed under the Apache 2.0 License. See LICENSE for details.
Author

    adiyn

## AI Disclosure
- Used AI as a tutoring resource for API references (no code generation).

(˶￣▽￣˶)ﾉ bai bai
