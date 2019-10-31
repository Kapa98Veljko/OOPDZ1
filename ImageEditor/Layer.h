#ifndef LAYER_H
#define LAYER_H
#include"Pixel.h"
class Layer {
public:
	Layer();
	void setOpacity(int i);//podesava providnost
	void setActivity(bool act);//podesava aktivnost
	int getOpacity();//vraca providnost
	bool getActivity();//vraca da li je izabrani sloj aktivan
	void setNext(Layer * sled);//za podesavanje pokazivaca next
	Layer* getNext();//vraca next
	void setLayer(Pixel*** newLayer);//za dodavanje novog sloja ali mi pre toga fali da kreiram praznu matricu 
	Pixel*** getLayer();//vraca ptptp odnosnu sliku koja je u listi n
private:
	//ono sto mi je potrebno za listu
	Pixel*** layer;//sloj
	Layer* next;//pokazivac na sledeci
	int layerOpacity;//providnost sloja
	bool activity;//da li je aktivan
};
#endif //LAYER_H