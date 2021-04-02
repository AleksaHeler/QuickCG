/*

TODO: 
  > makefile

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

    int x1, y1, x2, y2; //The initial line, too big for the screen
    int x3, y3, x4, y4; //Will become the clipped line
    x1 = -50; //This is outside the screen!
    y1 = -20; //This is outside the screen!
    x2 = 1000; //This is outside the screen!
    y2 = 1200; //This is outside the screen!
    clipLine(x1,y1, x2, y2, x3, y3, x4, y4); //the new line represents the part of the old line that is visible on screen
    drawLine(x3, y3, x4, y4, RGB_Red); //The newline is drawn as a red line
    drawCircle(100, 100, 30, RGB_Green); //a green unfilled circle
    drawDisk(200, 100, 20, RGB_Yellow); //a yellow filled circle
    drawRect(150, 150, 200, 200, RGB_Cyan); //acyan square

    /* Send frame to GPU to be displayed */
    redraw();
    /* Clear the screen so the old position of the ball becomes black again */
    cls();

  } /* End of main loop */
  
  /* Wait for user input */
  //sleep();
}
