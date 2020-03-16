#include "SharpnessFilter.h"

SharpnessFilter::SharpnessFilter()
{
	int size = 3;
	vector = new float[9];

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			vector[i * size + j] = -1;

	vector[4] = 9;
};