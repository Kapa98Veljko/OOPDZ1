#include "Layer.h"
#include<iostream>
#include<string>
using namespace std;

Layer::Layer()
{
	this->layer = nullptr;
	this->next = nullptr;
	this->layerOpacity = 0;
	this->sirina = 0;
}
Layer::~Layer()
{
	
	for (int i = 0; i < this->visina; i++) {
		for (int j = 0; j < this->sirina; j++) {
			delete this->layer[i][j];
		}
		delete[] this->layer[i];
	}
	delete[] this->layer;//brise ceo niz na koji pokazuje layer 
	layer = nullptr;
}
//Samo za aktivni sloj slike magarce
void Layer::setOpacity(int i)
{
	this->layerOpacity = i;
}



int Layer::getOpacity()
{
	return this->layerOpacity;
}



void Layer::setNext(Layer* sled)
{
	this->next = sled;
}

Layer* Layer::getNext()
{
	return this->next;
}

void Layer::setLayer(Pixel*** newLayer)
{
	this->layer = newLayer;
}

Pixel*** Layer::getLayer()
{
	return layer;
}

void Layer::setSirina(int i)
{
	this->visina = i;
}

void Layer::setVisina(int i)
{
	this->sirina = i;
}

