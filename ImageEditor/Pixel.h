#ifndef _PIXEL_H
#define _PIXEL_H
class Pixel {
public:
	Pixel();
	void setRed(unsigned int red);
	void setBlue(unsigned int blue);
	void setGreen(unsigned int green);
	unsigned int getRed();
	unsigned int getGreen();
	unsigned int getBlue();
private:
	unsigned int  r, g, b;

};
#endif //_PIXEL_H