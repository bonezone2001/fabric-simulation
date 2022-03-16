# Fabric Simulation C++

### Physics Constraint Example

This was just a fun little project I decided to do at like 4 AM one night before my bday!

This is a 2D simulation of cloth. Sorta. I just use it for simulating cloth but it can also simulate rope, chains and other things that are linked together via physics constraints.

The code is not the absolute best I've ever made, I made it really quickly after seeing somebody else do something similar for their project in java. I just sped through it so if the code isn't of the highest quality or I do things wrong. You have my appologises. It is also my first time creating my OWN CMake project. I've had experience building other people's but never creating my own.

Divider is a minimal project that's kept deliberately very small. When you build it using CMake/make (see below) it generates:

## Usage

### Prerequisites

You will need:

 * A modern C/C++ compiler
 * CMake 3+ installed (or really just kinda copy files manually into a project if you want)
 * A IDE or your choosing. I prefer Visual Studio on Windows.

### Building The Project

#### Git Clone

First we need to check out the git repo:

```bash
❯ git clone https://github.com/bonezone2001/fabric-simulation.git
❯ cd fabric-simulation
> mkdir build
> cd build
❯ cmake ..
```
You can skip the cmake commands and creating a build folder if you use the CMake GUI

### Controls

The simulation controls were kinda rushed so  I haven't created some nice-to-have features like resetting, line delete.

```base
> Left click - Add a Point
> Left click over point - Link point (click on another point to link the two)
> Right click over point - Lock point
> Middle click over point - Delete point and it's links
```

#### Contributing

Please submit any fixes or improvements, and I promise to review it as soon as I can:

 * [Submit Issues](https://github.com/bonezone2001/fabric-simulation/issues)
 * [Pull Requests](https://github.com/bonezone2001/fabric-simulation/pulls)

### License

&copy; 2022 Kyle Pelham.

Open sourced under Apache license, the terms of which can be read here — [Apache License](https://opensource.org/licenses/Apache-2.0).


### Acknowledgements

[Pixel Game Engine](https://github.com/OneLoneCoder/olcPixelGameEngine) created by OneLoneCoder is an amazingly easy to use 2D render library. Check him out!