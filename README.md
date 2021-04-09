# QuickCG
Following [tutorials](https://lodev.org/cgtutor/) to get more familiar with computer graphics and rendering for games. Major parts of the code were written by [Lode Vandevenne](https://lodev.org/cgtutor/legal.html), and credit for the idea and math goes to him, I'm just following his examples. For now mostly [Raycasting](https://lodev.org/cgtutor/raycasting.html).

## About
Semi 3D raycasting engine. Takes a map (2d matrix of integers which represent what is there) and draws elements "3D" by varying the height based on distance.

This has limitations: there is no height difference in map, stairs or jumping. But it works fast and is easy to make and will be used in some of my future projects.

In the way presented in this tutorial, an algorithm is used that's based on DDA or "Digital Differential Analysis". DDA is a fast algorithm typically used on square grids to find which squares a line hits (for example to draw a line on a screen, which is a grid of square pixels). So we can also use it to find which squares of the map our ray hits, and stop the algorithm once a square that is a wall is hit.

## Prerequisites
[Simple DirectMedia Layer](https://www.libsdl.org/) (SDL) library: ``` sudo apt install libsdl-dev ```
apt install libsdl2-image-dev

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
