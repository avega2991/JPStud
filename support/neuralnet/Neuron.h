#pragma once

#include "cocos2d.h"


class Neuron
{
private:
	std::string							m_name;
	int									m_weigth;

	// pointers has it's own weight too
	Neuron**							m_incomingLinks;
	Neuron**							m_outgoingLinks;

public:
	Neuron();


};