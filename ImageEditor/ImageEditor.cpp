#include "ImageEditor.h"
#include "Pixel.h"
#include<iostream>
#include<string>
using namespace std;

ImageEditor::ImageEditor()
{
	this->matrix = new Pixel**;//ISPRAVI AKO TREBA!!!!!!!!!!!
	this->height = 0;
	this->width = 0;
	this->sp = 0;
	this->isNamed = false;
	this->R = 0;
	this->B = 0;
	this->G = 0;
}

bool ImageEditor::loadImage(unsigned char* image)
{
	//PROVERENO
	//loading format
	if (image[this->sp] == 'b' || image[this->sp] == 'B') {
		this->ImageFormat[this->sp++] = 'B';
	}
	else {
		return false;
	}

	if (image[this->sp] == 'm' || image[this->sp] == 'M') {
		this->ImageFormat[this->sp++] = 'M';
	}
	else {
		return false;
	}
	//PROVERENO
	//loading name if there is any
	if (image[this->sp] == '=')
	{
		this->isNamed = true;
		while (image[this->sp] != '=')
		{
			this->ImageName += image[this->sp++];
		}
		this->sp++;//za prelazak preko jednako
	}
    //ili ima ili nema imena svakako trazi poziciju
	else if (!this->isNamed || this->sp % 4 != 0)
	{
		this->sp = FindPosition(this->sp);
	}
   //Ucitavanje sirine i visine
	this->width = FromHextoDec(this->sp);
	this->height =FromHextoDec(this->sp);

	this->sp++;
	this->sp = FindPosition(this->sp);

	for( int i = height - 1; i > 0; i--)
	{
		matrix[i] = new Pixel*;
		for (unsigned int j = 0; j < width; j++)
		{   //da li je potrebna dodatna konverzija
			matrix[i][j] = new Pixel;
			matrix[i][j]->setRed(image[this->sp++]);
			matrix[i][j]->setGreen(image[this->sp++]);
			matrix[i][j]->setBlue(image[this->sp++]);
		}
		this->sp = FindPosition(this->sp);
	}//mislim da je ovo kraj treba proveriti sa nekim


	return true;




}
//samo ime kaze
unsigned int ImageEditor::FindPosition(unsigned int sp)
{
	while (sp % 4)
	{
		sp++;
	}
	return sp;
}
int ImageEditor::fromHextoDec(int i)
{
	int c = 0;
	for(int i=0;i<4;i++)
	{
		c|=this->image[this->sp]
	}
}
//saveImage
unsigned char* ImageEditor::saveImage()
{
	unsigned char* image;

	//dodaj memoriju za sliku

	this->sp = 2;
	//sada je potrebno spakovati sliku 
	for (unsigned int i = 0; i < 2; i++)
	{
		image[i] = this->ImageFormat[i];

	}

	if (this->isNamed)
	{
		image[this->sp++] = '=';
		for (unsigned int i = 0; i < this->ImageName.length(); i++)
		{
			image[this->sp++] = ImageName[i];
		}
		image[this->sp++] = '=';
	}
	else
	{
		this->sp = FindPosition(this->sp);
	}

	//potrebno je vratiti sirinu i visinu u isto formatu
return image;
}
int ImageEditor::FindValue(char a, char b)
{
	int c = 0;
	for (int i = 2; i < 2; i++)
	{

	}
}
//Manipulacija slikom
/*void ImageEditor::addLayer()
{
}

void ImageEditor::deleteLayer()
{
}

void ImageEditor::selectLayer(int i)
{
}

void ImageEditor::invertColors()
{
}

void ImageEditor::toGrayScale()
{
}

void ImageEditor::blur(int size)
{
}

void ImageEditor::flipHorizontal()
{
}

void ImageEditor::flipVertical()
{
}

void ImageEditor::crop(int x, int y, int w, int h)
{
}*/
//Crtanje po slici
/*void ImageEditor::setActiveColor(string hex)
{
	bool isFormated = false;
	if (hex[0] == '#') {
		for (int i = 0; i < 8; i++)
		{

			if ((hex[i] >= '1' && hex[i] <= '10') || (hex[i] >= 'A' && hex[i] <= 'F'))
			{
				isFormated = true;
			}
			else
			{
				isFormated = false;
				//onemoguciti crtanje po slici i popravti kako treba da radi!!!
			}
		}


		this->R = FindValue(hex[1], hex[2]);
		this->B = FindValue(hex[3], hex[4]);
		this->G = FindValue(hex[5], hex[6]);
	}
}

void ImageEditor::fillRect(int x, int y, int w, int h)
{
}

void ImageEditor::eraseRect(int x, int y, int w, int h)
{
}*/
