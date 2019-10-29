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
	void setActiveColor(string hex);
	void fillRect(int x, int y, int w, int h);
	void eraseRect(int x,int y,int w, int h);
	int FindValue(char a,char b);

private:
	string ImageName;
	string ImageFormat;
	unsigned int height;//visina
	unsigned int width;//sirina
	bool isNamed;//is there a name
	unsigned int sp;
	Pixel*** matrix;
	//boje za crtanje 

	int R, B, G;

	//komentar

};

#endif//_IMAGE_H
