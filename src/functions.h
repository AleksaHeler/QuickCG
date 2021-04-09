
#include "quickcg/quickcg.h"
using namespace QuickCG;
using namespace std;


int bayer10x10[10][10] { // MAX 99
    55,78,91,14,37,50,73,96,19,32,
    89,2,25,48,61,84,7,20,43,66,
    13,36,59,72,95,18,31,54,77,90,
    47,60,83,6,29,42,65,88,1,24,
    71,94,17,30,53,76,99,12,35,58,
    5,28,41,64,87,0,23,46,69,82,
    39,52,75,98,11,34,57,70,93,16,
    63,86,9,22,45,68,81,4,27,40,
    97,10,33,56,79,92,15,38,51,74,
    21,44,67,80,3,26,49,62,85,8
};
int bayer9x9[9][9] = { // 80
    50, 71, 2,  23, 44, 56, 77, 17, 29,
    72, 12, 33, 45, 66, 6,  18, 39, 60,
    22, 43, 55, 76, 16, 28, 49, 70, 1,
    53, 65, 5,  26, 38, 59, 80, 11, 32,
    75, 15, 27, 48, 69, 0,  21, 42, 54,
    25, 37, 58, 79, 10, 31, 52, 64, 4,
    47, 68, 8,  20, 41, 62, 74, 14, 35,
    78, 9,  30, 51, 63, 3,  24, 36, 57,
    19, 40, 61, 73, 13, 34, 46, 67, 7
};

int bayer8x8[8][8] = { // MAX 63
    36,55,2,21,32,51,6,17,
    56,11,30,41,60,15,26,45,
    20,39,50,5,16,35,54,1,
    40,59,14,25,44,63,10,29,
    4,23,34,53,0,19,38,49,
    24,43,62,9,28,47,58,13,
    52,7,18,37,48,3,22,33,
    8,27,46,57,12,31,42,61
};

int bayer7x7[7][7] = { // MAX 48
    32,42,10,27,37,5,15,
    1,18,28,45,13,23,40,
    26,36,4,14,31,48,9,
    44,12,22,39,0,17,34,
    20,30,47,8,25,35,3,
    38,6,16,33,43,11,21,
    7,24,41,2,19,29,46
};

int bayer6x6[6][6] = { // MAX 35
    21, 30, 9,  18, 33, 6,
    1,  16, 25, 4,  13, 28,
    23, 32, 11, 20, 35, 8,
    3,  12, 27, 0,  15, 24,
    19, 34, 7,  22, 31, 10,
    5,  14, 29, 2,  17, 26
};

int bayer5x5[5][5] = { // MAX 24
    18,1,14,22,5,
    7,15,3,11,24,
    21,9,17,0,13,
    10,23,6,19,2,
    4,12,20,8,16
};

int bayer4x4[4][4] = { // MAX 15
    10,1,8,3,
    6,13,4,15,
    2,9,0,11,
    14,5,12,7
};

int bayer3x3[3][3] = { // MAX 8
    8,5,2,
    6,3,0,
    7,4,1
};

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