#include "SharpnessFilter_2.h"

SharpnessFilter_2::SharpnessFilter_2()
{
	int size = 3;

	vector = new float[size * size];
	vector[0] = 0; vector[1] = -1; vector[2] = 0;
	vector[3] = -1; vector[4] = 5; vector[5] = -1;
	vector[6] = 0; vector[7] = -1; vector[8] = 0;
};