# dis-rpC !

A lightweight C Rich Presence tool for discord with a CLI.

## Features

* **Cross-Platform:** Designed for Windows (WinAPI) and Linux (Unix Sockets). 
*Linux part isn't done yet :')*

## How it works

* Connects via the `\\.\pipe\discord-ipc-0` IPC pipe in the RAM (windows)

## Installation

### Pre-compiled
 * check releases

## Building from source on Microslop's Windownsyndrome

  **Requirements:** I recommend w64devkit (https://github.com/skeeto/w64devkit) but ig u can do whatever u want
  
  ```bash
  WINDOWS:
    > git clone https://codeberg.org/adiyn/dis-rpC.git
    > cd dis-rpC
    > make
  n just run dis-rpC.exe with or without the "-sdl" argument
  ```


### Roadmap

 * CLI + SDL user chooses through adding "-sdl" upon manual execution
 * add a GUI_dis-rpC.exe executable for the windows users to just click open 
 * initial release 
 * go outside


### License

Distributed under the Apache 2.0 License. See LICENSE for more information.

### Author

  * adiyn

# :3