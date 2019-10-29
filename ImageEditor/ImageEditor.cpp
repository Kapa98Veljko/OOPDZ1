#include "ImageEditor.h"
#include "Pixel.h"
#include<iostream>
using namespace std;
#include<string>

ImageEditor::ImageEditor()
{
	this->matrix = new Pixel**;
	this->height = 0;
	this->width = 0;
	this->sp = 0;
}

bool ImageEditor::loadImage(unsigned char* image)
{
	//is this done properly
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



	//loading name if there is any
	if (image[this->sp] == '=')
	{
		this->isNamed = true;
		while (image[this->sp] != '=')
		{
			this->ImageName += image[this->sp++];
		}
		this->sp++;
	}

	//if there is no name find the proper position 
	else if (!isNamed || this->sp % 4 != 0)
	{
		this->sp = FindPosition(this->sp);
	}


	//loading image height and width

	for (unsigned int i = 0; i < 4; i++)
	{
		this->width |= image[this->sp++] << i * 4;

	}

	for (unsigned int i = 0; i < 4; i++)
	{
		this->height |= image[this->sp++] << i * 4;

	}


	this->sp++;
	this->sp = FindPosition(this->sp);






	for (unsigned int i = height - 1; i >= 0; i--)
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
//saveImage
unsigned char* ImageEditor::saveImage()
{
	unsigned char* image;
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