#include "Pixel.h"

Pixel::Pixel()
{

}

void Pixel::setRed(unsigned int R)
{
	this->r = R;
}

void Pixel::setBlue(unsigned int B)
{
	this->b = B;
}

void Pixel::setGreen(unsigned int G)
{
	this->g = G;
}

unsigned char Pixel::getRed()
{
	return this->r;
}

unsigned char Pixel::getGreen()
{
	return this->g;
}

unsigned char Pixel::getBlue()
{
	return this->b;
}