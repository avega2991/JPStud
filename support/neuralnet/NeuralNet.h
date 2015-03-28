#pragma once

#include "support\neuralnet\Neuron.h"

struct Pixel
{
	unsigned char rgb[3];
};

class NeuralNet
{
private:
	Neuron										m_neuron[100]; // every neuron handles a 24x24 rect
	int											m_charactedID; // output

public:
	NeuralNet();

	int											defineCharacter(Pixel* pPixels, bool bSaveResult);

};
