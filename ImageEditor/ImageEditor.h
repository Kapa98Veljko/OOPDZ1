#ifndef _IMAGE_H
#define _IMAGE_H
#include"Layer.h"
#include "Pixel.h"
#include<string>
using namespace std;
class ImageEditor {
public:
	ImageEditor();
	bool loadImage(unsigned char* image);
	unsigned int FindPosition(unsigned int sp);
	int fillBlanks(int i,unsigned char* image);
	void packTheRest(Layer* glava,int i,unsigned char* image);
	unsigned char* saveImage();
	//Slojevi slike
	void addLayer();
	void deleteLayer();
	void selectLayer(int i);
	void setLayerOpacity(int i);//STA ZNACI SAMO OVO INT U ZAGRADI!!!!!!!!!!!!!
	//Manipulacijom slike
	//void invertColors();
	//void toGrayScale();
	//void blur(int size);
	//void flipHorizontal();
	//void flipVertical();
	//void crop(int x, int y, int w, int h);
	//Crtanje po slici
	//void setActiveColor(string hex);
	//void fillRect(int x, int y, int w, int h);
	//void eraseRect(int x, int y, int w, int h);
	
private:
	string ImageName;
	string ImageFormat;
	unsigned int height;//visina
	unsigned int width;//sirina
	bool isNamed;//is there a name
	unsigned int sp;//mozda i ne treba ovde
	Pixel*** original;
    int R, B, G;//boje za crtanje
	Layer* glava;
	Layer* active;//Pamti  koji je aktivan
	Layer* last;
	


};

#endif//_IMAGE_H
