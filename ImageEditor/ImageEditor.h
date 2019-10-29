#ifndef _IMAGE_H
#define _IMAGE_H
#include "Pixel.h"
#include<string>
using namespace std;
class ImageEditor {
public:
	ImageEditor();
	bool loadImage(unsigned char* image);
	unsigned int FindPosition(unsigned int sp);
	unsigned char* saveImage();


private:
	string ImageName;
	string ImageFormat;
	unsigned int height;//visina
	unsigned int width;//sirina
	bool isNamed;//is there a name
	unsigned int sp;
	Pixel*** matrix;

};

#endif//_IMAGE_H
