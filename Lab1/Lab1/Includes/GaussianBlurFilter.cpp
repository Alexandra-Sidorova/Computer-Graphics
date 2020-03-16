#include "GaussianBlurFilter.h"

GaussianBlurFilter::GaussianBlurFilter()
{
	createGaussianKernel(3, 2);
};

void GaussianBlurFilter::createGaussianKernel(int _radius, int _sigma)
{
	const unsigned int size = 2 * _radius + 1;
	float norm = 0;
	
	vector = new float[size * size];

	for(int i = -_radius; i <= _radius; i++)
		for (int j = -_radius; j <= _radius; j++)
		{
			vector[(i + _radius) * size + (j + _radius)] = (float)(exp((-1) * (i * i + j * j) / (_sigma * _sigma)));
			norm += vector[(i + _radius) * size + (j + _radius)];
		}

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			vector[i * size + j] = (float)(vector[i * size + j] / norm);
};