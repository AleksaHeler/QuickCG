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

<<<<<<< HEAD
int main(int argc, char *argv[])
{
  
=======
#define WIDTH 640
#define HEIGHT 480
#define FULLSCREEN 0
#define TITLE "Small Test Script"

int main(int argc, char *argv[]) {
  /* Make the window */
  screen(WIDTH, HEIGHT, FULLSCREEN, TITLE);

  /* The position of the circle; initially set it to the center of the screen */
  float x = w / 2, y = h / 2;
  /* The time of the current and the previous loop */
  float time, oldTime;

  /* While user doesnt exit program (esc or close button)*/
  while(!done()) {
    /* Draw part of the color palette*/
    for(int x = 0; x < w; x++)
      for(int y = 0; y < h; y++)
      {
        pset(x, y, ColorRGB(256*x / w, 256*y / h, 128));
      }
    
    /* Set the old time to the time of the previous loop */
    oldTime = time;
    //waitFrame(oldTime, 0.05); // wait for 50ms since last frame
    time = getTime(); //get the time since program start

    /* Get the current keystate */
    readKeys();

    /* If an arrow key is pressed, move the circle in its direction at a speed of 50 pixels/second */
    /*if(keyDown(SDLK_RIGHT)) x += 1000 * (time - oldTime) / 20.0;
    if(keyDown(SDLK_LEFT)) x -= 1000 * (time - oldTime) / 20.0;
    if(keyDown(SDLK_UP)) y -= 1000 * (time - oldTime) / 20.0;
    if(keyDown(SDLK_DOWN)) y += 1000 * (time - oldTime) / 20.0;*/
    float a = 5000.0 * (time - oldTime) / 20.0;
    if(keyDown(SDLK_RIGHT)) x += a;
    if(keyDown(SDLK_LEFT)) x -= a;
    if(keyDown(SDLK_UP)) y -= a;
    if(keyDown(SDLK_DOWN)) y += a;

    /* Draw a circle with radius 20 pixels at the position of the ball */
    drawDisk(int(x), int(y), 20, RGB_Black);

    /* Put some textx on the screen */
    print("Time:", 16, 16);
    print(getTime(), 64, 16);
    print("FPS:", 16, 32);
    print(1.0 / (time - oldTime), 64, 32);
    print("X:", 16, 48);
    print(x, 64, 48);
    print("Y:", 16, 60);
    print(y, 64, 60);

    /* Send frame to GPU to be displayed */
    redraw();
    /* Clear the screen so the old position of the ball becomes black again */
    cls();

  } /* End of main loop */
  
  /* Wait for user input */
  //sleep();
>>>>>>> 1ed7ee50fea0d9de3f34d285523e347af43700ec
}
