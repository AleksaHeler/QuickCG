#include <cmath>
#include <string>
#include <vector>
#include <iostream>
#include <stdlib.h> 

#include "quickcg/quickcg.h"
#include "functions.h"

using namespace QuickCG;
using namespace std;

void render_normal();
void render_monochrome();
void random_noise_render();
void bayer_dithering();

std::vector<ColorRGB> image;
unsigned long width, height;


int main(int argc, char *argv[])
{
    srand (time(NULL));
    if(loadImage(image, width, height, "pics/mushroom.png")) return 1;
    screen(width, height, 0, "An image");
/*
    render_normal();
    redraw();
    sleep();

    render_monochrome();
    redraw();
    sleep();

    random_noise_render();
    redraw();
    sleep();
*/
    bayer_dithering();
    redraw();
    sleep();
}


// Display original image
void render_normal() {
    for(int y = 0; y < h; y++)
    for(int x = 0; x < w; x++)
    {
        pset(x, y, image[y * w + x]);
    }
}

// Display image with only colors black and white
void render_monochrome() {
	reset_pixels();
	
	int i;
	ColorRGB rgb;
	for (i = 0; i < w * h; i++) {
		rgb = image[i%w + i/w * w]; 
		
		double lum = 0.3333*rgb.r + 0.3333*rgb.g + 0.3333*rgb.b;
		
		(lum > 128) ? pset(i%w, i/w, RGB_White) : pset(i%w, i/w, RGB_Black);
	}
	
	redraw();
}

void random_noise_render() {
    for(int y = 0; y < h; y++){
        for(int x = 0; x < w; x++){
            ColorRGB rgb = image[x+y*w];
		    int lum = 0.2126*rgb.r + 0.7152*rgb.g + 0.0722*rgb.b;
            lum += rand() % 256 - 128;
            (lum > 128) ? pset(x, y, RGB_White) : pset(x, y, RGB_Black);
        }
    }
}

void bayer_dithering(){
    /////   BEST LOOKING - 6   /////
    /*// 10x10
    for(int y = 0; y < h; y++){
        for(int x = 0; x < w; x++){
            ColorRGB rgb = image[x+y*w];
		    double lum = 0.3333*rgb.r + 0.3333*rgb.g + 0.3333*rgb.b;
            (lum/256.0 >  (double)bayer10x10[x%10][y%10]/99.0) ? pset(x, y, RGB_White) : pset(x, y, RGB_Black);
        }
    }
    redraw();
    sleep();
    // 9x9
    for(int y = 0; y < h; y++){
        for(int x = 0; x < w; x++){
            ColorRGB rgb = image[x+y*w];
		    double lum = 0.3333*rgb.r + 0.3333*rgb.g + 0.3333*rgb.b;
            (lum/256.0 >  (double)bayer9x9[x%9][y%9]/80.0) ? pset(x, y, RGB_White) : pset(x, y, RGB_Black);
        }
    }
    redraw();
    sleep();
    // 8x8
    for(int y = 0; y < h; y++){
        for(int x = 0; x < w; x++){
            ColorRGB rgb = image[x+y*w];
		    double lum = 0.3333*rgb.r + 0.3333*rgb.g + 0.3333*rgb.b;
            (lum/256.0 > (double)bayer8x8[x%8][y%8]/63.0) ? pset(x, y, RGB_White) : pset(x, y, RGB_Black);
        }
    }
    redraw();
    sleep();
    // 7x7
    for(int y = 0; y < h; y++){
        for(int x = 0; x < w; x++){
            ColorRGB rgb = image[x+y*w];
		    double lum = 0.3333*rgb.r + 0.3333*rgb.g + 0.3333*rgb.b;
            (lum/256.0 > (double)bayer7x7[x%7][y%7]/48.0) ? pset(x, y, RGB_White) : pset(x, y, RGB_Black);
        }
    }
    redraw();
    sleep();*/
    // 6x6
    for(int y = 0; y < h; y++){
        for(int x = 0; x < w; x++){
            ColorRGB rgb = image[x+y*w];
		    int lum = 0.3333*rgb.r + 0.3333*rgb.g + 0.3333*rgb.b;
            (lum/256.0 > (double)bayer6x6[x%6][y%6]/35.0) ? pset(x, y, RGB_White) : pset(x, y, RGB_Black);
        }
    }
    redraw();
    sleep();
    /*// 5x5
    for(int y = 0; y < h; y++){
        for(int x = 0; x < w; x++){
            ColorRGB rgb = image[x+y*w];
		    double lum = 0.3333*rgb.r + 0.3333*rgb.g + 0.3333*rgb.b;
            (lum/256.0 > (double)bayer5x5[x%5][y%5]/24.0) ? pset(x, y, RGB_White) : pset(x, y, RGB_Black);
        }
    }
    redraw();
    sleep();
    // 4x4
    for(int y = 0; y < h; y++){
        for(int x = 0; x < w; x++){
            ColorRGB rgb = image[x+y*w];
		    double lum = 0.3333*rgb.r + 0.3333*rgb.g + 0.3333*rgb.b;
            (lum/256.0 > (double)bayer4x4[x%4][y%4]/15.0) ? pset(x, y, RGB_White) : pset(x, y, RGB_Black);
        }
    }
    redraw();
    sleep();
    // 3x3
    for(int y = 0; y < h; y++){
        for(int x = 0; x < w; x++){
            ColorRGB rgb = image[x+y*w];
		    double lum = 0.3333*rgb.r + 0.3333*rgb.g + 0.3333*rgb.b;
            (lum/256.0 > (double)bayer3x3[x%3][y%3]/8.0) ? pset(x, y, RGB_White) : pset(x, y, RGB_Black);
        }
    }
    redraw();
    sleep();*/
}