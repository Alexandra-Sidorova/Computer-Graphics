#include "SobelXFilter.h"

SobelXFilter::SobelXFilter()
{
	int size = 3;

	vector = new float[size * size];
	vector[0] = -1; vector[1] = 0; vector[2] = 1;
	vector[3] = -2; vector[4] = 0; vector[5] = 2;
	vector[6] = -1; vector[7] = 0; vector[8] = 1;
};