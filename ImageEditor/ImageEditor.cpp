#include "ImageEditor.h"
#include "Pixel.h"
#include"Layer.h"
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
	this->active = nullptr;//cuvainformacije o aktivnom 
	this->last = nullptr;
}
ImageEditor::~ImageEditor()
{
	Layer* trenutni=new Layer;
	Layer* prethodni=new Layer;
	trenutni = this->glava;
	while (trenutni->getNext() != nullptr) 
	{
		prethodni->setNext(trenutni);
		for (int i = 0; this->height; i++)
		{
			for (int j = 0; j < this->width; j++)
			{
				delete prethodni->getLayer()[i][j];

			}
			delete[] prethodni->getLayer()[i];
		}
		delete[] prethodni->getLayer();
		prethodni=trenutni;
		trenutni = trenutni->getNext();
	}
	delete trenutni;
	delete prethodni;

	trenutni = nullptr;
	prethodni = nullptr;
}
bool ImageEditor::loadImage(unsigned char* image)
{

	//PROVERENO
	if (!image) { return false; }
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
	
	Pixel*** matrix =new Pixel**[this->height];//trenutna kopija
	
	for (int i = height - 1; i > 0; i--)
	{
	
		matrix[i] = new Pixel*[this->width];
		for (unsigned int j = 0; j < width; j++)
		{   //da li je potrebna dodatna konverzija
			
		
			matrix[i][j] = new Pixel();
			matrix[i][j]->setRed(image[this->sp++]);
			
			matrix[i][j]->setGreen(image[this->sp++]);
			
			matrix[i][j]->setBlue(image[this->sp++]);
		}
		//treba da se prekoce prazna mesta ako postoje
		this->sp = FindPosition(this->sp);
		
	}

	//sad imam sve matrice ovu matrix treba ubaciti u listu
	if(this->glava!=nullptr)
	{
		 Layer* trenutni=this->glava;
	     Layer* sledeci;
		while (this->glava->getNext() != nullptr) 
		{
			sledeci = trenutni->getNext();
			delete trenutni;
			trenutni = sledeci;
		}
	}
	  else
	{ 
		Layer* ptr1 = new Layer();
		ptr1->setLayer(matrix);
		this->glava=ptr1;
		this->active = ptr1;
		ptr1 = nullptr;
		delete ptr1;
		this->active =this->last= this->glava;
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

void ImageEditor::packTheRest(Layer* glava, int i, unsigned char* image)
{

}


	//saveImage
	unsigned char* ImageEditor::saveImage()
	{   
		
		unsigned int size = 10 + this->width * this->height;//format,visina,sirina,i broj piksela
		unsigned int k = 0;
		if (this->isNamed) { k += 2 + this->ImageName.length()+ 4-(( 4 + this->ImageName.length())%4) ; }
		else { k = 2; }
		size += k;
		unsigned char* image = new unsigned char[size];

		image[0] = 'B';
		image[1] = 'M';
		int sp = 2;//sp mi prati prvu ne popunjenu poziciju ujedno i broj elemenata niza jer indeks prvog ne popunjenog duzina samog niza
		if (this->isNamed)
		{
			image[sp] = '='; sp++;
			for (unsigned int i = 3; i < 3 + k; i++)
			{
				sp++;
				image[i] = this->ImageName[i];
			}
			image[sp] = '='; sp++; k += 4; //sp mi prati poslednji popunjeni indeks
		}
		
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
		sp += 4;
		sp = fillBlanks(sp, image);
	//sada treba sabrati sliku koju dobijam sabirajuci Layer-a
    //to da se ne bi gomilao kod mogu da uradim tako sto napravim funkkciju koja to radi
		packTheRest(this->glava,sp,image);


		return image;
	}

	void ImageEditor::freeMatrixfromLayer(Pixel*** matrix)
	{
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				delete matrix[i][j];
			}
			delete[] matrix[i];
		}
		delete[] matrix;
	}


//Manipulacija slikom
void ImageEditor::addLayer()
{
	Layer* ptr = new Layer();
	Pixel*** currentMatrix=new Pixel**;
	for (unsigned int i = 0; i < height; i++) 
	{
		currentMatrix[i] = new Pixel*;
		for (unsigned int j = 0; j < width; j++)
		{
			currentMatrix[i][j] = nullptr;
		}
	}
	ptr->setLayer(currentMatrix);

	//Nadovezivanje LinusTorvalds na kraj liste
	this->last = ptr;
	this->active = ptr;
	ptr = nullptr;
	delete ptr;
}
 void ImageEditor::deleteLayer()
{
	 Layer* prethodni = this->glava;
	 if (prethodni = this->active) 
	 {
		 std::cout << "<GRESKA!>Napravili ste gresku nije moguce izbrisati sloj sa ucitanom slikom!!!" << std::endl;
	 }
	 //ako nije uneta nijedna slika
	 else if (this->glava==nullptr) 
	 {
		 std::cout<<"<GRESKA>Greska ne postoji ni jedan ucitani sloj!!!"<<std::endl;
	 }
	 else
	 {    //ili dok ne dodje do kraja liste ili dok ne dodje iza aktivnog koji nije ucitana slika
		 while (prethodni->getNext() != nullptr && prethodni->getNext()!=this->active) 
		 {
			 prethodni = prethodni->getNext();
		 }

		 prethodni->setNext(this->active->getNext());
		 freeMatrixfromLayer(this->active->getLayer());
		 delete this->active;
		 this->active = prethodni;
	 }
}

void ImageEditor::selectLayer( int i)
{//pitati iliju da li i kako ide castovanje za float
	Layer* trenutni=this->glava;
	if (i < 0) 
	{
		std::cout<<"<GRESKA>Greska zadati sloj ne postoji"<<std::endl;
	}
	else if (i == 0) 
	{
		this->active = this->glava;
	}
	else
	{
		int k = 0;
		while (k < i && trenutni->getNext() != nullptr)
		{
			trenutni = trenutni->getNext();
			k++;
		}
		if (trenutni == nullptr)
		{
			std::cout << "<GRESKA>Greska prekoracili ste opseg!!!" << std::endl;
		}
		else 
		{
			this->active = trenutni;
		}
	
	}
	trenutni = nullptr;
	delete trenutni;
}

void ImageEditor::setLayerOpacity(int i)
{
	char c = 'N';
	if (i < 0 || i>100)
	{
		std::cout << "Ovo sto cinite je nedozvoljeno jer broj ili nije u opsegu ili nije pozitivan!!" << std::endl;
		bool wish = false;
		std::cout << "Da li zelite da znate gde ste pogresili?Y/N" << std::endl;
		
		std::cin >> c;
	}
	else if (c== 'Y'||c=='y') 
	
	{
		if (i < 0) { std::cout << "Broj je negativan!!!" << std::endl; }
		else if (i > 100) { std::cout << "Broj je veci od 100!!!" << std::endl; }
	}
	else{
		this->active->setOpacity(i);
	}
//provera za to da li je ceo broj!!!!!!
}



unsigned int ImageEditor::findAverage(int i,int j,int size)
{
	unsigned int prosek;
	int k = 0;



	return prosek;
}

Pixel*** ImageEditor::makeCopy(int visina,int sirina)
{
	Pixel*** copy = new Pixel * *[visina];
	for (int i = 0; i < visina; i++)
	{
		copy[i] = new Pixel * [sirina];
		for (int j = 0; j < sirina; j++)
		{
			copy[i][j] = nullptr;
			
		}
		
	}
	
	return copy;
}

void ImageEditor::invertColors()
{
	Pixel*** trenutni = this->active->getLayer();
	for (int i = 0; i < this->height; i++) 
	{
		for (int j = 0; j < this->width; j++) 
		{
			trenutni[i][j]->setRed(255-trenutni[i][j]->getRed());
			trenutni[i][j]->setGreen(255 - trenutni[i][j]->getGreen());
			trenutni[i][j]->setBlue(255 - trenutni[i][j]->getBlue());
		}
	}
	trenutni = nullptr;
}

void ImageEditor::toGrayScale()
{
	Pixel*** trenutni = this->active->getLayer();
	for (int i = 0; i < this->height; i++)
	{
		for (int j = 0; j < this->width; j++)
		{
			unsigned int togray= (unsigned int)(0.3*trenutni[i][j]->getRed())+ (unsigned int)(0.59*trenutni[i][j]->getGreen())+(unsigned int)(0.11*trenutni[i][j]->getBlue());
			trenutni[i][j]->setRed(togray);
			trenutni[i][j]->setGreen(togray);
			trenutni[i][j]->setBlue(togray);
		}
	}
	trenutni = nullptr;
	delete trenutni;
  //Ne zelim da mi vise nekih nekom greskom probije opseg i da pokazuju na nesto zapravo
  //Vazno Iliji si prepravio da bude sa kasovanjem inacu baguje !!!
}

void ImageEditor::blur(int size)
{
	int visina = 2 * size + 1;
	int sirina = 2 * size + 1;
	Pixel*** matrix = makeCopy(height,width);
	
	for (unsigned int i = 0; i < height; i++) 
	{
		for (unsigned int j = 0; j < width; j++) 
		{   
			unsigned int average = findAverage(i,j,size);
			matrix[i][j]->setRed(average);
			unsigned int average = findAverage(i,j,size);
			matrix[i][j]->setGreen(average);
			unsigned int average = findAverage(i, j, size);
			matrix[i][j]->setBlue(average);
		}
	}
}

void ImageEditor::flipHorizontal()
{
	Pixel*** trenutni = new Pixel**;
	Pixel*** copy = makeCopy(height,width);
	
	trenutni= this->active->getLayer();
	for (int i = 0; i < this->height; i++) 
	{
		int k = this->width - 1;
		for (int j = 0; j < width; j++) 
		{
			copy[i][k]->setBlue(trenutni[i][j]->getBlue());
			copy[i][k]->setBlue(trenutni[i][j]->getBlue());
			copy[i][k--]->setBlue(trenutni[i][j]->getBlue());

		}
	}
	this->active->setLayer(copy);
	//izbrisati trenutni 
	freeMatrixfromLayer(trenutni);

}

void ImageEditor::flipVertical()
{
	Pixel*** trenutni = new Pixel**;
	Pixel*** copy = makeCopy(height,width);

	trenutni = this->active->getLayer();
	int k = this->height - 1;
	for (unsigned int i= 0; i<this->height; i++) 
	{
		for (unsigned int j = 0; j < this->width; j++)
		{
			copy[i][j]->setBlue(trenutni[i][k]->getBlue());
			copy[i][j]->setRed(trenutni[i][k]->getRed());
			copy[i][j]->setGreen(trenutni[i][k--]->getGreen());
		}
	}
	this->active->setLayer(copy);
	freeMatrixfromLayer(trenutni);
}

void ImageEditor::crop(int x, int y, int w, int h)
{	//zavrsena 
	if (x < 0 || y < 0 || w < 0 || h < 0||x>width||y>height|| ((h + y) > height)|| ((x + w) > width))
	{
		std::cout<<"<GESKA>Pogresno formatirano!!!"<<std::endl;
	}
	else {
		int visina = h + y;
		int sirina = w + x;
		Layer* trenutni = glava;
		while (trenutni->getNext() != nullptr) {
			Pixel*** matrix = makeCopy(visina, sirina);
			Pixel*** pom = trenutni->getLayer();
			//sada je potrebno da se u novoj matrici dodaju odgovarajuce boje
			for (unsigned int i = 0; i < visina; i++)
			{
				matrix[i] = new Pixel*[sirina];
				for (unsigned int j = 0; j < sirina; j++)
				{
					matrix[i][j] = new Pixel(pom[i + y][j + x]->getRed(), pom[i + y][j + x]->getGreen(), pom[i + y][j + x]->getBlue());
				}
			}
			freeMatrixfromLayer(trenutni->getLayer());//brise staru
			trenutni->setLayer(matrix);
			trenutni = trenutni->getNext();
			matrix = nullptr;
		}

		//to je na kraju
		width = w;
		height = h;
	}
}
//Crtanje po slici
void ImageEditor::setActiveColor(string hex)
{
	bool format = true; int i = 1;
	if (hex[0] != '#') { format = false; }
	while (i < 7) 
	{
		if (hex[i] < 'a' || hex[i]> 'f' || hex[i] > 'F' || hex[i] < 'A') 
		{
			format =false;
		}
		i++;
	}
	if (format) 
	{
		for (int i = 1; i < 7; i++)
		{
			if (hex[i] == 'a') { hex[i] = 'A'; }
			if (hex[i] == 'b') { hex[i] = 'B'; }
			if (hex[i] == 'c') { hex[i] = 'C'; }
			if (hex[i] == 'd') { hex[i] = 'D'; }
			if (hex[i] == 'e') { hex[i] = 'E'; }
			if (hex[i] == 'f') { hex[i] = 'F'; }
		
		}
		this->R = fromHextoDecimal(hex[1],hex[2]);
		this->G= fromHextoDecimal(hex[3], hex[4]);
		this->B = fromHextoDecimal(hex[5], hex[6]);
	
	}
}

unsigned int ImageEditor::fromHextoDecimal(char a, char b)
{
	unsigned int boja = 0;
	if (a >= 'A') { boja = 16 * (a - 'A' + 10); }
	else (boja = 16 * (a - '0' + 10));
	if (b >= 'A') { boja = (b - 'A' + 10); }
	else (boja = (b - '0' + 10));
	return boja;
}

void ImageEditor::fillRect(int x, int y, int w, int h)
{//(x,y) koordianata gornjeg levog ugla
 //(w,h) sirina i visina pravougaonika ako izlazi van opsega onda samo do kraja matrice
 //prvo cu da preracunam visinu i sirinu i treba ispitati da li je pokazivac nullptr jer NE treba sve na pocetku postavlajti na 0,0,0
	int visina = y+x;
	int sirina = w+h;
	//DA LI MI OVDE TREBA DA SE DODELI MEMORIJA JA MISLIM DA NE!!!!
	Pixel*** matrica;
	matrica = this->active->getLayer();

	
	if (visina > this->height) 
	{
		visina = this->height;
	}
	if (sirina > this->width) 
	{
		sirina = this->width;
	}
	for (int i = y; i < visina; i++) 
	{
		for (int j = x; j < sirina; j++) 
		{
			if (matrica[i][j] == nullptr) 
			{
				matrica[i][j] = new Pixel(this->R,this->G,this->B);
			}
		}
	}

	//DA LI JE OVO POTREBNO DA SE UNISTI!!!!! I NA KOJI NACIN SE TO RADI
}

void ImageEditor::eraseRect(int x, int y, int w, int h)
{
	Pixel*** matrica=active->getLayer();
	int visina = y + h;
	int sirina = x + w;

	if (visina > height) 
	{
		visina = height;
	}
	if (sirina > width) 
	{
		sirina = width;
	}

	for (unsigned int i = y; i < visina; i++) 
	{
		for (unsigned int j = h; j < sirina; j++) 
		{
			delete matrica[i][j];
			matrica[i][j] = nullptr;
		}
	}
}
