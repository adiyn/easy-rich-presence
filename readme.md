# dis-rpC !

A lightweight C Rich Presence tool for discord with a CLI.

## Features

* **Cross-Platform:** Designed for Windows (WinAPI) and Linux (Unix Sockets). 
*Linux part isn't done yet :')*

## How it works

* Connects via the `\\.\pipe\discord-ipc-0` IPC pipe in the RAM (windows)

## Installation

### Pre-compiled
 * get the .exe on windows

## Building from source

  **Requirements:** Make, w64devkit (https://github.com/skeeto/w64devkit) or mingw,
  link with -luser32 -lws2_32 -lshlwapi -lwinmm -lole32 -loleaut32 to compile.
  
  ```bash
  WINDOWS:
    > git clone https://codeberg.org/adiyn/dis-rpC.git
    > cd dis-rpC
    > make
  run dis-rpC.exe
  ```


### Roadmap

 * revamp into an SDL app, keep CLI implementation to bare minimum for debugging
 * go outside


### License

Distributed under the Apache 2.0 License. See LICENSE for more information.

### Author

  * adiyn

# :3