#include "Layer.h"
#include<iostream>
#include<string>
using namespace std;

Layer::Layer()
{
	this->layer = nullptr;
	this->next = nullptr;
	this->activity = false;
	this->layerOpacity = 100;
}
//Samo za aktivni sloj slike magarce
void Layer::setOpacity(int i)
{
	this->layerOpacity = i;
}

void Layer::setActivity(bool act)
{
	this->activity = act;
}

int Layer::getOpacity()
{
	return this->layerOpacity;
}

bool Layer::getActivity()
{
	return this->activity;
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
	return this->layer;
}

