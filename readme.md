# dis-rpC !

A lightweight Rich Presence tool with a CLI, made in C.
Connects directly to apps via IPC pipes, avoiding bloated dependencies.

## Features

* **Performance:** Written in C, practically zero resource usage.
* **Standalone:** No Python, Node.js, or heavy libraries required.
* **Cross-Platform:** Designed for Windows (WinAPI) and Linux (Unix Sockets). *Linux part isn't done yet.*

## How it works

dis-rpC bypasses  web APIs and communicates directly with your local clients using IPC.
* **example:**
  * **Discord :** Connects via `\\.\pipe\discord-ipc-0` in the ram

## Installation

### Pre-compiled
 WIP.

## Building from source

  **Requirements:** GCC, Make.
  
  ```bash
  git clone https://codeberg.org/adiyn/dis-rpC.git
  cd dis-rpC
  make
  ./app
  ```


### Roadmap

  * make a CLI.
  * Implement a conf file for custom images and status text n stuff.


### License

Distributed under the Apache 2.0 License. See LICENSE for more information.

### Author

  * adiyn

# :3