# Chained Reaction
![](https://chemistrytalk.org/wp-content/uploads/2023/03/640px-NuclearReaction.svg-1.png)

## Overview
This project simulates some chemical reaction using multi processing architecture program. It's written in C with the help of some standard library functions for some things like:
- semaphores
- shared memory
- signals
- process forks/execs

It also uses [Raylib](https://github.com/raysan5/raylib) to perform some fancy rendering to avoid doing the whole simulation in the terminal (cuz it's kinda not cool and boring)

## Installation
This is just a temporary thing. This project will eventually have a more complex build system in the future.

1. Install [Raylib](https://github.com/raysan5/raylib) on your machine
2. Just cd into the project directory and run:
```shell
make
make run
```

## Features
- [ ] build system
    - [x] global project makefile invokes specific entity makefile
    - [x] master makefile
    - [ ] atom makefile
    - [ ] activator makefile
    - [ ] supplier makefile
    - [ ] who's gonna link raylib anyway?
- [ ] a module for every Entity process
    - [ ] master
    - [ ] atom
    - [ ] activator
    - [ ] supplier
