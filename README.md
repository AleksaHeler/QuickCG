# QuickCG
Following [tutorials](https://lodev.org/cgtutor/) to get more familiar with computer graphics and rendering for games

## Prerequisites
[Simple DirectMedia Layer](https://www.libsdl.org/) (SDL) library: ``` sudo apt install libsdl-dev ```

## Makefile

``` make main ``` - compile src/main.cpp file (currently empty)

``` make run ``` - compile and then **run** the src/main.cpp file

``` make raycaster-flat ``` - compile flat raycaster example file (src/raycaster_flat.cpp)

``` make raycaster-textured ``` - compile textured raycaster example file (src/raycaster_textured.cpp)

``` make run-raycaster-flat ``` - compile and then **run** flat raycaster example

``` make run-raycaster-textured ``` - compile and then **run** textured raycaster example

``` make clean ``` - delete output files

## Structure
``` sh
.
├── LICENSE
├── makefile
├── pics
│   ├── barrel.png
│   ├── bluestone.png
│   ├── colorstone.png
│   ├── eagle.png
│   ├── greenlight.png
│   ├── greystone.png
│   ├── mossy.png
│   ├── pillar.png
│   ├── purplestone.png
│   ├── redbrick.png
│   └── wood.png
├── README.md
└── src
    ├── examples
    │   ├── image.cpp
    │   ├── rainbow.cpp
    │   └── text.cpp
    ├── main.cpp
    ├── quickcg
    │   ├── LICENCE
    │   ├── quickcg.cpp
    │   └── quickcg.h
    ├── raycaster_flat.cpp
    └── raycaster_textured.cpp

4 directories, 23 files
```
