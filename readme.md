# dis-rpC !

A lightweight C Rich Presence app in pure C and CLI.

## Features

* **Cross-Platform:** Designed for Windows (WinAPI) and Linux (Unix Sockets). 
*Linux part isn't done yet :')*

## How it works

* Connects via the `\\.\pipe\discord-ipc-0` IPC pipe. 

## Installation

### Pre-compiled
 * check releases

## Building from source on Microslop's Windownsyndrome

  **Requirements:** I recommend w64devkit (https://github.com/skeeto/w64devkit) but ig u can do whatever u want
  
  ```bash
  Win / linux:
    > git clone https://codeberg.org/adiyn/dis-rpC.git
    > cd dis-rpC
    > make
  ```

### Roadmap
 * fix the various bugs, unsafe code, use better C types. 
 * windows version (to polish)
 * remove the ugly #ifdef \_win32 and \_\_linux__ giant blocks and instead define variables depending on the os ? 
 * linux version (todo)
 * go outside (todo)

### License

Distributed under the Apache 2.0 License. See LICENSE for more information.

### Author

  * adiyn, use of GenAI : as tutoring (socratic)

# :3