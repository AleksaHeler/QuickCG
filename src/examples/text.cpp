/*

COMPILE: g++ main.cpp quickcg/quickcg.cpp -lSDL -O3
RUN: ./a.out

*/

#include <cmath>
#include <string>
#include <vector>
#include <iostream>

#include "quickcg/quickcg.h"

using namespace QuickCG;
using namespace std;

int main(int argc, char *argv[])
{
  screen(256, 256, 0, "Text");
  //draw some texts
  print("Hello World!");
  print("I am spooky green text!", 20, 20, ColorRGB(0, 255, 0), 1, ColorRGB(0, 128, 0));

  //draw an integer variable
  int number = 1337;
  print(number, 16, 40, ColorRGB(0, 255, 255));

  //draw a floating point variable
  float pi = 3.1415926535897932384626433832795;
  print(pi, 0, 8);

  //draw every single character of the font
  for(int x = 0; x < 16; x++)
  for(int y = 0; y < 16; y++)
  {
    drawLetter(x + 16 * y, 100 + x * 8, 100 + y * 8, ColorRGB(255, 255, 255), 1, ColorRGB(255, 0, 0));
  }

  //draw multiple texts in a row easily by using the return value
  int pos;
  pos = print("All", 0, 70, RGB_Red);
  pos = print("your", pos / h, pos % h, RGB_Green);
  pos = print("base", pos / h, pos % h, RGB_Blue);
  pos = print("are", pos / h, pos % h, RGB_Yellow);
  pos = print("belong", pos / h, pos % h, RGB_Cyan);
  pos = print("to", pos / h, pos % h, RGB_Magenta);
  pos = print("us!!", pos / h, pos % h, RGB_White);

  redraw();
  sleep();  
}
