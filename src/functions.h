
#include "quickcg/quickcg.h"
using namespace QuickCG;
using namespace std;



void reset_pixels() {
    for(int y = 0; y < h; y++)
    for(int x = 0; x < w; x++) {
        pset(x, y, RGB_Black);
    }
}

ColorRGB getRGB(Uint32* pixels, int x, int y) {
	ColorRGB rgb; rgb.r = 0; rgb.g = 0; rgb.b = 0;
	
	if (x < 0 || x >= w || y < 0 || y >= h) return rgb;
	
	rgb.r = (pixels[y * w + x] & 0xff);
	rgb.g = (pixels[y * w + x] & 0xff00) >> 8;
	rgb.b = (pixels[y * w + x] & 0xff0000) >> 16;
	
	return rgb;
}

void setRGB(Uint32* pixels, int x, int y, ColorRGB rgb) {
	if (x < 0 || x >= w || y < 0 || y >= h) return;
	
	pixels[y * w + x] = 0xff000000 + (rgb.r) + (rgb.g << 8) + (rgb.b << 16);
}

ColorRGB difRGB(ColorRGB from, ColorRGB to) {
	ColorRGB dif;
	dif.r = to.r - from.r;
	dif.g = to.g - from.g;
	dif.b = to.b - from.b;
	
	return dif;
}

ColorRGB addRGB(ColorRGB a, ColorRGB b) {
	ColorRGB sum;
	sum.r = a.r + b.r;
	sum.g = a.g + b.g;
	sum.b = a.b + b.b;
	
	if (sum.r > 255) sum.r = 255; if (sum.r < 0) sum.r = 0;
	if (sum.g > 255) sum.g = 255; if (sum.g < 0) sum.g = 0;
	if (sum.b > 255) sum.b = 255; if (sum.b < 0) sum.b = 0;
	
	return sum;
}

ColorRGB divRGB(ColorRGB rgb, double d) {
	ColorRGB div;
	div.r = (int)((double)rgb.r/d);
	div.g = (int)((double)rgb.g/d);
	div.b = (int)((double)rgb.b/d);
	
	return div;
}

ColorRGB mulRGB(ColorRGB rgb, double d) {
	ColorRGB mul;
	mul.r = (int)((double)rgb.r*d);
	mul.g = (int)((double)rgb.g*d);
	mul.b = (int)((double)rgb.b*d);
	
	return mul;
}

double distRGB(ColorRGB from, ColorRGB to) {
	ColorRGB dif = difRGB(from, to);
	double dist = dif.r*dif.r + dif.g*dif.g + dif.b*dif.b;
	
	return dist;
}

ColorRGB nearestRGB(ColorRGB rgb, ColorRGB rgbs[], int numRGBs) {
	double dist = -1, tempDist;
	ColorRGB nearest;
	
	int i;
	for (i = 0; i < numRGBs; i++) {
		tempDist = distRGB(rgb, rgbs[i]);
		
		if (tempDist < dist || dist < 0) {
			dist = tempDist;
			nearest = rgbs[i];
		}
	}
	
	return nearest;
}