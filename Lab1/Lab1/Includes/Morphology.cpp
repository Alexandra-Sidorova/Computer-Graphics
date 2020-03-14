#include "Morphology.h"

Morphology::Morphology()
{
	height = weight = 3;
	
	mask = new bool[height * weight];
	for (int i = 0; i < height * weight; i++)
		mask[i] = true;
};

Morphology::Morphology(bool* _mask, int _height, int _weight) : height(_height), weight(_weight)
{
	mask = new bool[height * weight];
	for (int i = 0; i < height * weight; i++)
		mask[i] = _mask[i];
};