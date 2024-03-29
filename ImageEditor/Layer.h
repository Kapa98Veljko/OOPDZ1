#ifndef LAYER_H
#define LAYER_H
#include"Pixel.h"

class Layer {
public:
	Layer();
	~Layer();
	void setOpacity(int i);//podesava providnost
	int getOpacity();//vraca providnost
	void setNext(Layer * sled);//za podesavanje pokazivaca next
	Layer* getNext();//vraca next
	void setLayer(Pixel*** newLayer);//za dodavanje novog sloja ali mi pre toga fali da kreiram praznu matricu 
	Pixel*** getLayer();//vraca ptptp odnosnu sliku koja je u listi slojeva
	void setSirina(int i);
	void setVisina(int i);
private:
	//ono sto mi je potrebno za listu
	Pixel*** layer;//sloj
	Layer* next;//pokazivac na sledeci
	unsigned int layerOpacity;//providnost sloja
	int visina;
	int sirina;

};
#endif //LAYER_H