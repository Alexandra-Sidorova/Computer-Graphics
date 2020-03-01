#include "MotionBlurFilter.h"

MotionBlurFilter::MotionBlurFilter()
{
	int size = 2 * mRadius + 1;
	vector = new float[size * size];

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
		{
			if (i == j)
				vector[i * size + j] = 1.0f / size;
			else
				vector[i * size + j] = 0;
		}
};