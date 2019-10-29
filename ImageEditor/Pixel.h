#ifndef _PIXEL_H
#define _PIXEL_H
class Pixel {
public:
	Pixel();
	void setRed(unsigned int R);
	void setBlue(unsigned int B);
	void setGreen(unsigned int G);
	unsigned char getRed();
	unsigned char getGreen();
	unsigned char getBlue();
private:
	int r, g, b;

};
#endif //_PIXEL_H