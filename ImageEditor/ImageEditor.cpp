#include "ImageEditor.h"
#include "Pixel.h"
#include<iostream>
#include<string>
using namespace std;

ImageEditor::ImageEditor()
{
	this->ImageName = "";
	this->height = 0;
	this->width = 0;
	this->sp = 0;
	this->isNamed = false;
	this->R = 0;
	this->B = 0;
	this->G = 0;
	this->glava = nullptr;
	this->original = nullptr;
	this->matrix = nullptr;
}

bool ImageEditor::loadImage(unsigned char* image)
{
	int size = 0;
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
	this->width = (int)image[this->sp++] + ((int)image[this->sp++]) * 256 + ((int)image[this->sp++]) * 256 * 256 + ((int)image[this->sp++]) * 256 * 256 * 256;
	this->height= (int)image[this->sp++] + ((int)image[this->sp++]) * 256 + ((int)image[this->sp++]) * 256 * 256 + ((int)image[this->sp++]) * 256 * 256 * 256;
	//visina i sirina ucitane i postavljen sp na prvu poziciju nakon njih
	//nalazi deljivu sa cetiri ako nije na njoj
	
	this->sp = FindPosition(this->sp);
	

	//sada bi trebalo da se doda odma u sloj i da se postavi na aktivan i da se podesi neka neprovidnost TO MOZDA I NE TREBA!!!!!!!! sloj
	for (int i = height - 1; i > 0; i--)
	{
		this->original[i] = new Pixel*;
		this->matrix[i] = new Pixel*;
		for (unsigned int j = 0; j < width; j++)
		{   //da li je potrebna dodatna konverzija
			this->original[i][j] = new Pixel;
			this->matrix[i][j] = new Pixel;
			this->original[i][j]->setRed(image[this->sp]);
			this->matrix[i][j]->setRed(image[this->sp++]);
			this->original[i][j]->setGreen(image[this->sp]);
			this->matrix[i][j]->setGreen(image[this->sp++]);
			this->original[i][j]->setBlue(image[this->sp]);
			this->matrix[i][j]->setBlue(image[this->sp++]);
		}
		//treba da se prekoce prazna mesta ako postoje
		this->sp = FindPosition(this->sp);
		
	}

	//sad imam sve matrice ovu matrix treba ubaciti u listu
	if(this->glava!=nullptr)
	{
		Layer* trenutni = this->glava;
		Layer* sledeci;
		while (this->glava->getNext() != nullptr) 
		{
			sledeci = trenutni->getNext();
			delete trenutni;
			trenutni = sledeci;
		}
		delete this->glava;
	}
	  else
	{ 
		Layer* ptr1 = new Layer();
		ptr1->setLayer(this->matrix);
		this->glava=ptr1;
	}
	
	return true;
}
//Nalazi poziciju deljivu sa cetiri i vraca njen indeks gde sp treba da bude
unsigned int ImageEditor::FindPosition(unsigned int sp)
{  //vraca na mesto koje je deljivo sa 4
	while (sp % 4)
	{
		sp++;
	}
	return sp;
}

int ImageEditor::fillBlanks(int i,unsigned char* image)//OVO MOZE DA JEBE STVAR!!!!!!!
{
	while (i % 4) 
	{
		image[i] = '0';
		i++;
	}
	return i;
}


	//saveImage
	unsigned char* ImageEditor::saveImage()
	{   
		
		unsigned int size = 8 + this->width * this->height;//format,visina,sirina,i broj piksela
		unsigned int k = 2;
		if (this->isNamed) { k += 2 + this->ImageName.length(); }
		//
		size += k;
		unsigned char* image = new unsigned char[size];

		image[0] = 'B';
		image[1] = 'M';
		int sp = 2;
		if (this->isNamed)
		{
			image[2] = '=';
			for (int i = 3; i < 3 + k; i++)
			{
				sp++;
				image[i] = this->ImageName[i];
			}
			image[3 + k] = '='; k += 4; sp++;//sp mi prati poslednji popunjeni indeks
		}
		sp++;//prvi ne popunjeni
		sp=fillBlanks(sp, image);
		
		//sada treba popuniti visinu i sirinu
		
		int w = this->width / 256;
		int h = this->height / 256;

		for(int i=0;i<4;i++)
		{
			image[sp] = (unsigned char)w;
			image[sp + 4] = (unsigned char)h;
			w /=  256;
			h /= 256;
			sp++;
		}
		sp = fillBlanks(sp, image);
	
	
		return image;
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
