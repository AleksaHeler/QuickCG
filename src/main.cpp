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
    if(loadImage(image, width, height, "pics/bridge1.png")) return 1;
    screen(width, height, 0, "An image");
/*
    render_normal();
    redraw();
    sleep();

    render_monochrome();
    redraw();
    sleep();
*/
    random_noise_render();
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

}