# Chain Reaction
![Chain Reaction picture](https://chemistrytalk.org/wp-content/uploads/2023/03/640px-NuclearReaction.svg-1.png)

## Overview
This project simulates some chemical reaction using multi processing architecture program. It's written in C with the help of some standard library functions for some things like:
- semaphores
- shared memory
- signals
- process forks/execs

It also uses [Raylib](https://github.com/raysan5/raylib) to perform some fancy rendering to avoid doing the whole simulation in the terminal (cuz it's kinda not cool and boring)

### Beware
I'm using POSIX APIs for Unix syscalls (not SystemV's) as there are many more advantages (google is your friend) in doing so. 

I'm also using `arc4random()` as RNG instead of the usual combo `srand(time(NULL))` + `rand()` as it's more reliable, easier to use and more stable with a multi-process context. On Ubuntu (and maybe other distros as well) it's not part of standard C lib, so to use it you should:
1. install `libbsd-dev` package on your machine
2. include the BSD header in your code
```c 
#include <bsd/stdlib.h>
```
3. link the executable with `-lbsd` flag, for example:
```shell
gcc -o your_prog -Wall prog.c -lbsd
```

## Installation
This is just a temporary thing. This project will eventually have a more complex build system in the future.

1. Install [Raylib](https://github.com/raysan5/raylib) on your machine
2. Just cd into the project directory and run:
```shell
make
make run
```

## Todos
- [ ] build system
    - [X] global project makefile invokes specific entity makefile
    - [X] master makefile
    - [X] atom makefile
    - [X] activator makefile
    - [ ] supplier makefile
    - [ ] who's gonna link raylib anyway?

- [ ] a module for every Entity process
    - [ ] master
        - [X] InitAtoms()
        - [X] init activator
        - [ ] init supplier
    - [X] atom
    - [X] activator
        - [X] SplitAtom()
    - [ ] supplier

- [X] semaphore APIs

- [X] shared memory APIs

- [ ] signals
    - [X] atom handlers
    - [X] activator handlers
    - [ ] supplier handlers

- [ ] application logics
    - [X] system total energy
    - [ ] system total waste
    - [?] atom heirarchy

- [ ] some useful tools
    - [/] dynamic collections
    - [X] RNG (arc4random)
    - [ ] loggers
        - [X] error logger
        - [ ] file loggers
            - [ ] master
            - [ ] atom
            - [ ] activator
            - [ ] supplier
    - [X] N process barrier
