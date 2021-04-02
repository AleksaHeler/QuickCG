#include <cmath>
#include <string>
#include <vector>
#include <iostream>

#include "quickcg/quickcg.h"

using namespace QuickCG;
using namespace std;

int main(int argc, char *argv[])
{
  std::vector<ColorRGB> image;
  unsigned long w, h;
  if(loadImage(image, w, h, "pics/barrel.png")) return 1;
  screen(w, h, 0, "An image");

  //draw each pixel of the image
  for(int y = 0; y < h; y++)
  for(int x = 0; x < w; x++)
  {
    pset(x, y, image[y * w + x]);
  }

  redraw();
  sleep();
}
