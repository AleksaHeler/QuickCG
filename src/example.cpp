#include <cmath>
#include <string>
#include <vector>
#include <iostream>

#include "quickcg/quickcg.h"

using namespace QuickCG;
using namespace std;

#define FULLSCREEN 0

int main(int argc, char *argv[])
{
  /* DRAW A RAINBOW AND SOME TEXT */
  screen(860, 640, FULLSCREEN, "Small Test Script");
  for(int x = 0; x < w; x++)
  for(int y = 0; y < h; y++)
  {
    //pset(x, y, ColorRGB(0, 128 + 128 * sin(x / 8.0), 0));
    pset(x, y, ColorRGB(256*x / w, 256*y / h, 128));
  }
  print("Hello, world!", 16, 16);

  std::string test;
  test.resize(20);

  /* DRAW A FACE */
  /*screen(256,256, 0, "A Face!"); 
  drawDisk(128, 128, 100, ColorRGB(255, 128, 200)); 
  drawDisk(88, 100, 10, ColorRGB(0, 0, 255)); 
  drawDisk(168, 100, 10, ColorRGB(0, 0, 255)); 
  drawLine(88, 150, 168, 150, ColorRGB(255, 0, 0));*/

  redraw();
  sleep();
}
