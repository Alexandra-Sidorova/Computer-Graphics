#include "SobelYFilter.h"

SobelYFilter::SobelYFilter()
{
	int size = 3;

	vector = new float[size * size];
	vector[0] = -1; vector[1] = -2; vector[2] = -1;
	vector[3] = 0; vector[4] = 0; vector[5] = 0;
	vector[6] = 1; vector[7] = 2; vector[8] = 1;
};