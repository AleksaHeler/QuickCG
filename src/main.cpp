/*
Copyright (c) 2004, Lode Vandevenne
All rights reserved.

COMPILE: g++ *.cpp -lSDL -O3
RUN: ./a.out
*/

#include <cmath>
#include <string>
#include <vector>
#include <iostream>

#include "quickcg.h"
using namespace QuickCG;
using namespace std;

//place the example code below here:

int main(int /*argc*/, char */*argv*/[])
{
  screen(256, 256, 0, "Small Test Script");
  for(int x = 0; x < w; x++)
  for(int y = 0; y < h; y++)
  {
    //pset(x, y, ColorRGB(0, 128 + 128 * sin(x / 8.0), 0));
    pset(x, y, ColorRGB(x, y, 128));
  }
  print("Hello, world!", 16, 16);

  std::string test;
  test.resize(20);

  redraw();
  sleep();
}
