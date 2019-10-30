#ifndef LAYER_H
#define LAYER_H
#include"Pixel.h"
class Layer {
public:
	Layer();
	void setOpacity(int i);
	void setActivity(bool act);
	int getOpacity();
	bool getActivity();
	void setNext(Layer * sled);
	Layer* getNext();
	void setLayer(Pixel*** newmatrix);
	Pixel*** getLayer();
private:
	//ono sto mi je potrebno za listu
	Pixel*** layer;
	Layer* next;
	int layerOpacity;
	bool activity;
};
#endif //LAYER_H