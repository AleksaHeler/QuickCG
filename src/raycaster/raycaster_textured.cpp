/*
  Tutorial and copyright: https://lodev.org/cgtutor/raycasting.html

  A lot is similar to raycaster_flat.cpp, and only new parts are commented here

  g++ *.cpp -lSDL -O3 -W -Wall -ansi -pedantic
  g++ *.cpp -lSDL
*/

#include <cmath>
#include <string>
#include <vector>
#include <iostream>

#include "quickcg/quickcg.h"
using namespace QuickCG;

// 640*480
// 1280*1024
// 1920*1080
#define screenWidth 1280     /* Screen size */
#define screenHeight 1024
#define texWidth 64         /* Texture size */
#define texHeight 64
#define mapWidth 24         /* Map size */
#define mapHeight 24
/* Wether to generate our own textures or use .png */
#define USE_GENERATED_TEXTURES 0

/* Different world map that flat raycaster */
int worldMap[mapWidth][mapHeight]=
{
  {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
  {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
  {4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
  {4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
  {4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
  {4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
  {4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
  {4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
  {4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
  {4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
  {4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
  {4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
  {6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
  {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
  {6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
  {4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
  {4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
  {4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
  {4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
  {4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
};

Uint32 buffer[screenHeight][screenWidth];

int main(int /*argc*/, char */*argv*/[])
{
    double posX = 22.0, posY = 11.5;    // x and y start position
    double dirX = -1.0, dirY = 0.0;     // initial direction vector
    double planeX = 0.0, planeY = 0.66; // the 2d raycaster version of camera plane

    double time = 0;    // time of current frame
    double oldTime = 0; // time of previous frame

    std::vector<Uint32> texture[8]; // Array of vectors: 8 textures, each a vector with (width * height) pixels
    for(int i = 0; i < 8; i++) texture[i].resize(texWidth * texHeight);

    /* Create the screen */
    screen(screenWidth,screenHeight, 0, "Raycaster");

    /* Generate some simple textures */
#if USE_GENERATED_TEXTURES
    for(int x = 0; x < texWidth; x++)
    for(int y = 0; y < texHeight; y++) {
        int xorcolor = (x * 256 / texWidth) ^ (y * 256 / texHeight);
        //int xcolor = x * 256 / texWidth;
        int ycolor = y * 256 / texHeight;
        int xycolor = y * 128 / texHeight + x * 128 / texWidth;
        texture[0][texWidth * y + x] = 65536 * 254 * (x != y && x != texWidth - y); //flat red texture with black cross
        texture[1][texWidth * y + x] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
        texture[2][texWidth * y + x] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
        texture[3][texWidth * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
        texture[4][texWidth * y + x] = 256 * xorcolor; //xor green
        texture[5][texWidth * y + x] = 65536 * 192 * (x % 16 && y % 16); //red bricks
        texture[6][texWidth * y + x] = 65536 * ycolor; //red gradient
        texture[7][texWidth * y + x] = 128 + 256 * 128 + 65536 * 128; //flat grey texture
    }
#else
    /* Use .png textures */
    unsigned long tw, th;
    loadImage(texture[0], tw, th, "pics/eagle.png");
    loadImage(texture[1], tw, th, "pics/redbrick.png");
    loadImage(texture[2], tw, th, "pics/purplestone.png");
    loadImage(texture[3], tw, th, "pics/greystone.png");
    loadImage(texture[4], tw, th, "pics/bluestone.png");
    loadImage(texture[5], tw, th, "pics/mossy.png");
    loadImage(texture[6], tw, th, "pics/wood.png");
    loadImage(texture[7], tw, th, "pics/colorstone.png");
#endif

  /* Start the main game loop */
  while(!done())
    {
        /* Go trough the screen horizontaly from left to right */
        for(int x = 0; x < w; x++)
        {
            /* Calculate ray position and direction */
            double cameraX = 2 * x / (double)w - 1; //x-coordinate in camera space
            double rayDirX = dirX + planeX*cameraX;
            double rayDirY = dirY + planeY*cameraX;

            //which box of the map we're in
            int mapX = int(posX);
            int mapY = int(posY);

            /* Length of ray from current position to next x or y-side */
            double sideDistX;
            double sideDistY;

            /* Length of ray from one x or y-side to next x or y-side */
            double deltaDistX = std::abs(1 / rayDirX);
            double deltaDistY = std::abs(1 / rayDirY);
            double perpWallDist;

            /* What direction to step in x or y-direction (either +1 or -1) */
            int stepX;
            int stepY;

            int hit = 0; //was there a wall hit?
            int side; //was a NS or a EW wall hit?

            /* Calculate step and initial sideDist */
            if(rayDirX < 0) {
                stepX = -1;
                sideDistX = (posX - mapX) * deltaDistX;
            }
            else {
                stepX = 1;
                sideDistX = (mapX + 1.0 - posX) * deltaDistX;
            }
            if(rayDirY < 0) {
                stepY = -1;
                sideDistY = (posY - mapY) * deltaDistY;
            }
            else {
                stepY = 1;
                sideDistY = (mapY + 1.0 - posY) * deltaDistY;
            }

            /* Perform DDA */
            while (hit == 0)
            {
                /* Jump to next map square, OR in x-direction, OR in y-direction */
                if(sideDistX < sideDistY) {
                    sideDistX += deltaDistX;
                    mapX += stepX;
                    side = 0;
                } else {
                    sideDistY += deltaDistY;
                    mapY += stepY;
                    side = 1;
                }
                /* Check if ray has hit a wall */
                if(worldMap[mapX][mapY] > 0) hit = 1;
            }

            /* Calculate distance of perpendicular ray (Euclidean distance will give fisheye effect!) */
            if(side == 0) perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
            else          perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

            /* Calculate height of line to draw on screen */
            int lineHeight = (int)(h / perpWallDist);

            /* Calculate lowest and highest pixel to fill in current stripe */
            int drawStart = -lineHeight / 2 + h / 2;
            if(drawStart < 0) drawStart = 0;
            int drawEnd = lineHeight / 2 + h / 2;
            if(drawEnd >= h) drawEnd = h - 1;

            /* Texturing calculations */
            /* Number 5 on map corresponds to texture index 4 and so on, so we subract 1 */
            int texNum = worldMap[mapX][mapY] - 1;

            /* Calculate value of wallX */
            double wallX; //where exactly the wall was hit
            if(side == 0) wallX = posY + perpWallDist * rayDirY;
            else          wallX = posX + perpWallDist * rayDirX;
            wallX -= floor((wallX));

            /* X coordinate on the texture */
            int texX = int(wallX * double(texWidth)); // pos on the wall texture
            if(side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
            if(side == 1 && rayDirY < 0) texX = texWidth - texX - 1;

            /* TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster */
            /* How much to increase the texture coordinate per screen pixel */
            double step = 1.0 * texHeight / lineHeight;
            /* Starting texture coordinate */
            double texPos = (drawStart - h / 2 + lineHeight / 2) * step;

            /* Draw the texture vertical stripe */
            for(int y = drawStart; y < drawEnd; y++) {
                /* Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow */
                int texY = (int)texPos & (texHeight - 1);
                texPos += step;
                Uint32 color = texture[texNum][texHeight * texY + texX];
                /* Make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and" */
                if(side == 1) color = (color >> 1) & 8355711;
                buffer[y][x] = color;
            }
        }

        /* Draw to screen the buffer which we have been working with */
        drawBuffer(buffer[0]);

        /* Clear the buffer (instead of cls) */
        for(int y = 0; y < h; y++) for(int x = 0; x < w; x++) buffer[y][x] = 0; 

        /* Timing for input and FPS counter */
        oldTime = time;
        time = getTicks();

        double frameTime = (time - oldTime) / 1000.0; //frametime is the time this frame has taken, in seconds
        print(1.0 / frameTime); //FPS counter
        redraw();

        /* Speed modifiers */
        double moveSpeed = frameTime * 5.0; //the constant value is in squares/second
        double rotSpeed = frameTime * 3.0; //the constant value is in radians/second

        readKeys();

        /* Move forward if no wall in front of you */
        if(keyDown(SDLK_UP)) {
            if(worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false) posX += dirX * moveSpeed;
            if(worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
        }
        /* Move backwards if no wall behind you */
        if(keyDown(SDLK_DOWN)) {
            if(worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
            if(worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
        }
        /* Rotate to the right */
        if(keyDown(SDLK_RIGHT)) {
            /* Both camera direction and camera plane must be rotated */
            double oldDirX = dirX;
            dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
            dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
            double oldPlaneX = planeX;
            planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
            planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
        }
        /* Rotate to the left */
        if(keyDown(SDLK_LEFT)) {
            /* Both camera direction and camera plane must be rotated */
            double oldDirX = dirX;
            dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
            dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
            double oldPlaneX = planeX;
            planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
            planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
        }
        if(keyDown(SDLK_ESCAPE)) {
            break;
        }
    }
}
